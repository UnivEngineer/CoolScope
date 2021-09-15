//------------------------------------------------------------------------------------------
// PWM fans
//------------------------------------------------------------------------------------------
CFansController fans;
//------------------------------------------------------------------------------------------

void  CFansController::Init()
{
  // Enable outputs for Timer 1
  pinMode(PWM_1A_PIN, OUTPUT); // out PWM signal of timer 1A to pin 9
  pinMode(PWM_1B_PIN, OUTPUT); // out PWM signal of timer 1B to pin 10

  // Enable outputs for Timer 2
  //pinMode(PWM_2_PIN,  OUTPUT); // out PWM signal of timer 2 to pin 3

  // Enable interrupt input for fan tachometers
  pinMode(TACH_1_PIN, INPUT_PULLUP); // with pullup resistor
  pinMode(TACH_2_PIN, INPUT_PULLUP); // with pullup resistor

  // set tachISR to be triggered when the signal on the sense pin goes low
  attachInterrupt(digitalPinToInterrupt(TACH_1_PIN), fans.tach1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(TACH_2_PIN), fans.tach2ISR, FALLING);

  // Init timers
  setupTimer1();
  //setupTimer2();

  // Shutdown fans
  setPWM1A(0);
  setPWM1B(0);
  //setPWM2(0);
}

//------------------------------------------------------------------------------------------

void  CFansController::Update()
{
  if ((varCoolingMode.value == C_OFF) || settings.isPowerLost())
  {
    state.fanDuty1 = state.fanDuty2 = 0;
  }
  else
  {
    // Update fan speed based on temerature
    float dT = fabs(state.tempDelta);
    float target_dT = varTargetDeltaT.getf();
    target_dT = max(target_dT, 0.05f);
  
    const float tolerance = 2.0f;
    float lerpf = (dT - target_dT) / (tolerance * target_dT);
    int   lerpi = clampi(int(floor(lerpf * 100.0f) + 0.5f), 0, 100);
    int   duty  = mixi(varKeepingSpeed.value, varCoolingSpeed.value, lerpi);
  
    state.fanDuty1 = state.fanDuty2 = duty;
  
    // If target delta T reached, change fans mode
    if (lerpf <= 0.0f)
    {
      switch (varCoolingMode.value)
      {
        case C_COOL_AND_BLOW: state.fanDuty2 = 0; break;
        case C_COOL_AND_SUCK: state.fanDuty1 = 0; break;
        case C_COOL_AND_OFF:  state.fanDuty1 = state.fanDuty2 = 0; break;
      }
    }
  }

  // Set fans duty
  setPWM1A(state.fanDuty1);
  setPWM1B(state.fanDuty2);

  // Calculate RPM
  uint32_t t = millis();
  uint32_t timePassed = t - lastTimeRPM;
  if (timePassed >= FAN_RPM_COUNT_TIME)
  {
    // Protect this piece of code from interrupts
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
      state.fanRPM1 = (fanCounter1 * 30000ul) / timePassed;
      state.fanRPM2 = (fanCounter2 * 30000ul) / timePassed;
      state.fanRPM1 = min(state.fanRPM1, 9999ul);
      state.fanRPM2 = min(state.fanRPM2, 9999ul);
      fanCounter1 = 0;
      fanCounter2 = 0;
    }
    lastTimeRPM = t;
  }

  if (state.fanRPM1 != 0) fanStuck1 = false;
  if (state.fanRPM2 != 0) fanStuck2 = false;

  timePassed = t - lastTimeStuck;
  if (timePassed >= FAN_STUCK_WAIT_TIME)
  {
    fanStuck1 = (state.fanDuty1 != 0) && (state.fanRPM1 == 0);
    fanStuck2 = (state.fanDuty2 != 0) && (state.fanRPM2 == 0);
    lastTimeStuck = t;
  }
}

//------------------------------------------------------------------------------------------

void  CFansController::Off()
{
  state.fanDuty1 = state.fanDuty2 = 0;
  setPWM1A(0);
  setPWM1B(0);
}

//------------------------------------------------------------------------------------------

bool CFansController::isStuck()
{
  return (varFanStuckAlarm.value == 1) && !settings.isPoweredByUSB() && (fanStuck1 || fanStuck2);
}

//------------------------------------------------------------------------------------------
// Configure Timer 1 (pins 9, 10) to output 25kHz PWM

void CFansController::setupTimer1()
{
    //Set PWM frequency to about 25khz on pins 9, 10 (timer 1 mode 10, no prescale, count to 320)
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
    TCCR1B = (1 << CS10)   | (1 << WGM13);
    ICR1   = 640; // 640 clock periods (16 Mhz) = 25kHz
    OCR1A  = 0;
    OCR1B  = 0;
}

//------------------------------------------------------------------------------------------
// Configure Timer 2 (pin 3) to output 25kHz PWM. Pin 11 will be unavailable for output in this mode

void CFansController::setupTimer2()
{
    //Set PWM frequency to about 25khz on pin 3 (timer 2 mode 5, prescale 8, count to 79)
    TIMSK2 = 0;
    TIFR2  = 0;
    TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << WGM22)  | (1 << CS21);
    OCR2A  = 79; // 79 clock periods * 8 (16 Mhz / 8) = 25,316 kHz
    OCR2B  = 0;
}

//------------------------------------------------------------------------------------------

void CFansController::setPWM1A(int duty)
{
    OCR1A = (uint16_t)((duty * 640l) / 100l);
}

//------------------------------------------------------------------------------------------

void CFansController::setPWM1B(int duty)
{
    OCR1B = (uint16_t)((duty * 640l) / 100l);
}

//------------------------------------------------------------------------------------------

void CFansController::setPWM2(int duty)
{
    OCR2B = (uint8_t)((duty * 79l) / 100l);
}

//------------------------------------------------------------------------------------------
uint32_t volatile CFansController::fanCounter1 = 0;
uint32_t volatile CFansController::fanCounter2 = 0;
//------------------------------------------------------------------------------------------
// Interrupt handler, stores the timestamps of the last 2 interrupts and handles debouncing

void CFansController::tach1ISR()
{
  fanCounter1++;
}

//------------------------------------------------------------------------------------------
// Interrupt handler, stores the timestamps of the last 2 interrupts and handles debouncing

void CFansController::tach2ISR()
{
  fanCounter2++;
}

//------------------------------------------------------------------------------------------
