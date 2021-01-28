#include "PrintTables.h"

EFI_STATUS

UefiMain ( IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable )
{
  EFI_STATUS Status;
  EFI_TIME *Time = NULL;  				//3

  EFI_SYSTEM_TABLE *gST = NULL;  		//2
  EFI_BOOT_SERVICES *gBS = NULL;  		//2
  EFI_RUNTIME_SERVICES *gRT = NULL;  	//2
  
  EFI_SHELL_PARAMETERS_PROTOCOL *eSPP = NULL;  	//1
  UINTN Argc;  									//1
  CHAR16 **Argv;  								//1
  
  gST = SystemTable;  			//2
  gBS = gST->BootServices;  	//2
  gRT = gST->RuntimeServices;	//2

  Status = gBS->OpenProtocol (ImageHandle, &gEfiShellParametersProtocolGuid, (VOID **)&eSPP, ImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL );  //1
  if (!EFI_ERROR(Status))
  {
      Argc = eSPP->Argc;    //1
      Argv = eSPP->Argv;	//1
  }

  if ( Argc>1 && Argc<3 )
  {
	Print (L"Argc : %d || Argv[1] : %s\n",Argc, Argv[1]);	//1
  }
  else if ( Argc>2 )
  {
	Print (L"More than one Command Line Input\n");			//1
  }

  Print (L"System Table Address Location in Hex : %p\n",gST);			//2
  Print (L"Boot Service Table Address Location in Hex : %p\n",gBS);  	//2
  Print (L"Runtime Service Table Address Location in Hex : %p\n",gRT);	//2

  Status = gBS->AllocatePool ( EfiBootServicesData, sizeof(EFI_TIME), (void **)&Time);  //3
  if(EFI_ERROR(Status))
  {
	Print(L"AllocatePool ");  			//3
	return Status;
  }
  
  Status = gRT->GetTime ( Time, NULL);	//3
  if(EFI_ERROR(Status))
  {
	Print(L"GetTime ");  				//3
	return Status;
  }
  
  Print (L"%d:%d:%d %d:%d:%d\n", Time->Day, Time->Month, Time->Year, Time->Hour, Time->Minute, Time->Second);  //3
  
  return Status;
}