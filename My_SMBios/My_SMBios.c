#include "My_SMBios.h"

#define SMBIOS_TABLE_GUID {0xeb9d2d31,0x2d88,0x11d3,{0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}}

EFI_STATUS

UefiMain ( IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable )
{
  EFI_STATUS Status;
  
  EFI_SYSTEM_TABLE *gST = NULL;
  EFI_CONFIGURATION_TABLE *gCT = NULL;
  EFI_GUID VT = SMBIOS_TABLE_GUID;
  VOID *SMBT = NULL;
  
  gST = SystemTable;
  gCT = gST->ConfigurationTable;
  
  Print (L"Configuration Table Address : %p\n",gCT);
  
  Status = EfiGetSystemConfigurationTable  ( (EFI_GUID *) &VT, (VOID **) &SMBT );
  if(EFI_ERROR(Status))
  {
	Print (L"EfiGetSystemConfigurationTable : ERROR\n");
	return Status;
  }

  Print ( L"Configuration Table Address : %p\n", VT );
  
  return Status;
}