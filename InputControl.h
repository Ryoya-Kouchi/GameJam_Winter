#pragma once
//makuroteigi
#define XINPUT_BUTTON_MAX (16)    //controllernobuttonnokazu

void InputControl_Initialize(void);
void InputControl_Update(void);
int Get_ButtonDown_play1(int button);    //ositasyunnkann
int Get_ButtonDown_play2(int button);   //ositasyunkan
