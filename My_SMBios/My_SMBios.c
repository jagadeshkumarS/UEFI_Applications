#include "My_SMBios.h"

EFI_STATUS

UefiMain ( IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable )
{
  EFI_STATUS Status;
  
  EFI_SYSTEM_TABLE *gST = NULL;
  EFI_CONFIGURATION_TABLE *gCT = NULL;
  EFI_GUID VT = {0xf2fd1544,0x9794,0x4a2c,{0x99,0x2e,0xe5,0xbb,0xcf,0x20,0xe3,0x94}};
  VOID *SMBT = NULL;

  gST = SystemTable;
  gCT = gST->ConfigurationTable;
  
  Print ( L"Configuration Table Address : %p\n",gCT );
  
  Status = EfiGetSystemConfigurationTable ( (EFI_GUID *) &VT, (VOID **) &SMBT );
  if(EFI_ERROR(Status))
  {
	Print ( L"EfiGetSystemConfigurationTable : ERROR\n" );
	return Status;
  }

  Print ( L"SMBios Table Address : %p\n", SMBT );
  
/*
  UINTN *mem = (UINTN *)SMBT - 16;
  int length, i;
  unsigned char checksum;
  while (1)
  {
    if (mem[0] == '_' && mem[1] == 'S' && mem[2] == 'M' && mem[3] == '_')
	{
      length = (int) mem[5];
      checksum = 0;
      for(i = 0; i < length; i++)
	  {
        checksum += (unsigned char)mem[i];
      }
      if(checksum == 0) break;
    }
    mem += 16;
  }
  Print ( L"%p\n",mem );
*/

  return EFI_SUCCESS;
}