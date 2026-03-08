
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
 // 140715ae0
void FUN_140715ae0(longlong param_1,char param_2,undefined8 param_3)

{
  uint uVar1;
  longlong lVar2;

  lVar2 = *(longlong *)(param_1 + 8);
  if ((lVar2 != 0) && (param_2 == *(char *)(lVar2 + 0x332))) {
    uVar1 = *(uint *)(lVar2 + 0x2f8);
    *(undefined4 *)(lVar2 + 0x2f8) = 0;
    if (1 < uVar1) {
      Actor::Kill_impl2(param_3,_gPlayerCharacter,0,CONCAT71((int7)((ulonglong)lVar2 >> 8),1),0);  // 140715b27
    }
    *(undefined1 *)(*(longlong *)(param_1 + 8) + 0x332) = 0;
  }
  return;
}

