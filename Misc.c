#include<windows.h>

//Display Related settings

//Fullscreen
void fullscreen()
{
keybd_event(VK_MENU,0x38,0,0);
keybd_event(VK_RETURN,0x1c,0,0);
keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

//Horizontal Alignment
void Halign(){
	printf("\t\t\t");
}
//Vertical Alignment
void Valign(){
	printf("\n\n\n\n\n\n\n\n\n\n");
}

//Close Console
void CloseConsole(){
	keybd_event(VK_MENU,0xb8,0 , 0); //Alt Press
	keybd_event(VK_F4,0xbe,0 , 0); // Tab Press
	keybd_event(VK_F4,0xbe, KEYEVENTF_KEYUP,0); // Tab Release
	keybd_event(VK_MENU,0xb8,KEYEVENTF_KEYUP,0); // Alt Release
}
