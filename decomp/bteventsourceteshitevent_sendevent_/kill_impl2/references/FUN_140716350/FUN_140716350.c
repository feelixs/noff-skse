
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
// 140716350
void FUN_140716350(longlong param_1,longlong param_2,float param_3)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  longlong lVar5;
  longlong lStackX_8;

  lVar5 = *(longlong *)(param_1 + 8);
  if ((((lVar5 != 0) && (*(int *)(lVar5 + 0x2f8) != 0)) &&
      ((*(uint *)(param_2 + 200) & 0x1c0000) == 0)) && (*(char *)(lVar5 + 0x332) == '\0')) {
    *(float *)(lVar5 + 0x2d4) = *(float *)(lVar5 + 0x2d4) - param_3;
    lVar5 = *(longlong *)(param_1 + 8);
    if (*(float *)(lVar5 + 0x2d4) <= 0.0) {
      *(undefined4 *)(lVar5 + 0x2d4) = 0;
      lVar5 = *(longlong *)(param_1 + 8);
      if ((lVar5 != 0) && (*(char *)(lVar5 + 0x332) == '\0')) {
        uVar3 = *(uint *)(lVar5 + 0x2f8);
        *(undefined4 *)(lVar5 + 0x2f8) = 0;
        if (1 < uVar3) {
          Actor::Kill_impl2(param_2,_gPlayerCharacter,0,1,0); // 140716423
        }
        *(undefined1 *)(*(longlong *)(param_1 + 8) + 0x332) = 0;
        lVar5 = *(longlong *)(param_1 + 8);
      }
    }
  }
  if ((lVar5 != 0) && (0.0 < *(float *)(lVar5 + 0x2d8))) {
    *(float *)(lVar5 + 0x2d8) = *(float *)(lVar5 + 0x2d8) - param_3;
    lVar5 = *(longlong *)(param_1 + 8);
    if (*(float *)(lVar5 + 0x2d8) <= 0.0) {
      *(undefined4 *)(lVar5 + 0x2d8) = 0;
      *(uint *)(param_2 + 0x204) = *(uint *)(param_2 + 0x204) & 0xffffbfff;
      lVar5 = *(longlong *)(param_1 + 8);
    }
  }
  if (lVar5 != 0) {
    if (0.0 < *(float *)(lVar5 + 0x2dc)) {
      *(float *)(lVar5 + 0x2dc) = *(float *)(lVar5 + 0x2dc) - param_3;
      lVar5 = *(longlong *)(param_1 + 8);
      if (*(float *)(lVar5 + 0x2dc) <= 0.0) {
        *(undefined4 *)(lVar5 + 0x2dc) = 0;
        *(uint *)(param_2 + 0xcc) = *(uint *)(param_2 + 0xcc) & 0xffffdfff;
        lVar5 = *(longlong *)(param_1 + 8);
      }
    }
    if ((lVar5 != 0) && (0.0 < *(float *)(lVar5 + 0x204))) {
      lStackX_8 = 0;
      cVar4 = Actor::GetMount(param_2,&lStackX_8);
      if ((cVar4 == '\0') || ((*(uint *)(lStackX_8 + 200) & 0x1c0000) == 0)) {
        *(float *)(*(longlong *)(param_1 + 8) + 0x204) =
             *(float *)(*(longlong *)(param_1 + 8) + 0x204) - param_3;
      }
      if (*(float *)(*(longlong *)(param_1 + 8) + 0x204) <= 0.0) {
        *(undefined4 *)(*(longlong *)(param_1 + 8) + 0x204) = 0xff7fffff;
        FUN_140673960(param_2,0);
      }
      if (lStackX_8 != 0) {
        LOCK();
        piVar1 = (int *)(lStackX_8 + 0x28);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if ((iVar2 - 1U & 0x3ff) == 0) {
          (**(code **)(*(longlong *)(lStackX_8 + 0x20) + 8))();
        }
      }
    }
  }
  return;
}

