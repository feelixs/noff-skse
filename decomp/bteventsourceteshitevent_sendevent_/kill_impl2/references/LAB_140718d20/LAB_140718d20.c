
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
// 140718d20
void UndefinedFunction_140718d20(longlong param_1,longlong param_2,float param_3)

{
  uint uVar1;
  longlong lVar2;

  lVar2 = *(longlong *)(param_1 + 8);
  if ((((lVar2 != 0) && (*(int *)(lVar2 + 0x2f8) != 0)) &&
      ((*(uint *)(param_2 + 200) & 0x1c0000) == 0)) && (*(char *)(lVar2 + 0x332) == '\0')) {
    *(float *)(lVar2 + 0x2d4) = *(float *)(lVar2 + 0x2d4) - param_3;
    if (*(float *)(*(longlong *)(param_1 + 8) + 0x2d4) <= 0.0) {
      *(undefined4 *)(*(longlong *)(param_1 + 8) + 0x2d4) = 0;
      lVar2 = *(longlong *)(param_1 + 8);
      if ((lVar2 != 0) && (*(char *)(lVar2 + 0x332) == '\0')) {
        uVar1 = *(uint *)(lVar2 + 0x2f8);
        *(undefined4 *)(lVar2 + 0x2f8) = 0;
        if (1 < uVar1) {
          Actor::Kill_impl2(param_2,_gPlayerCharacter,param_2,1,0); // 140718dba
        }
        *(undefined1 *)(*(longlong *)(param_1 + 8) + 0x332) = 0;
      }
    }
  }
  return;
}

