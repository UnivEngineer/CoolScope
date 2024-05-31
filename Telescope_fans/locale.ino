//------------------------------------------------------------------------------------------
char mesBuffer [LINE_LENGTH+1];
char mesBuffer2[LINE_LENGTH+1];
//------------------------------------------------------------------------------------------

const char * LoadMessage(CTextMessageId n)
{
#ifdef BI_LANG
  if (varDisplayLang.value == 1)
    strcpy_P(mesBuffer, (char*)pgm_read_word(&(mer_table[n])));
  else
#endif
    strcpy_P(mesBuffer, (char*)pgm_read_word(&(mes_table[n])));

  mesBuffer[LINE_LENGTH] = 0; // protection

#ifdef DEBUG
  //Serial.print(F("LoadMessage: "));
  //Serial.println(mesBuffer);
#endif 
 
  return mesBuffer;
}

//------------------------------------------------------------------------------------------

const char * LoadMessage2(CTextMessageId n)
{
#ifdef BI_LANG
  if (varDisplayLang.value == 1)
    strcpy_P(mesBuffer, (char*)pgm_read_word(&(mer_table[n])));
  else
#endif
    strcpy_P(mesBuffer2, (char*)pgm_read_word(&(mes_table[n])));

  mesBuffer2[LINE_LENGTH] = 0; // protection

#ifdef DEBUG
  //Serial.print(F("LoadMessage2: "));
  //Serial.println(mesBuffer2);
#endif 

  return mesBuffer2;
}

//------------------------------------------------------------------------------------------
