extern "C"
{

/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/

#include "def.h"

//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
//
//



int AddIn_main(int isAppli, unsigned short OptionNum)
{
	unsigned int key;
start:
	cout.clear();
	cin.clear();


// Insert your code down here:
	char * algorithms[] = {"Jacobi", "Gauss-Seidel", "Gaussian elimination", "LU decomposition"};
    int select = pop_menu(algorithms,"Select Algorithm:",4,0,0);
	switch (select)
	{
		case 0:
			Jacobi();
			break;
		case 1:
			Gauss_Seidel();
			break;
		case 2:
			Gaussian_elimination();
			break;
		case 3:
			LU_solve();
			break;
		default:
			cout.clear();
			cout << "Not avaliable, so sorry for this." << endl;
			cout << "Press EXE or EXIT to return." << endl;
	}


// Return to the beginning after process
	while (1)
	{
		GetKey(&key);
		if ( key == KEY_CTRL_EXE || key == KEY_CTRL_EXIT ) break;
	}
    goto start;
    return 1;
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

}
