// 140655640
void FUN_140655640(undefined8 param_1,longlong param_2,undefined4 param_3,undefined8 param_4,
                  undefined1 param_5,undefined1 param_6)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 auStackX_10 [8];
  undefined4 auStack_98 [2];
  undefined4 uStack_90;
  undefined4 uStack_88;
  undefined8 uStack_80;
  float fStack_78;
  undefined4 uStack_70;
  undefined4 uStack_68;
  undefined4 uStack_60;
  undefined1 uStack_58;
  undefined1 uStack_50;

  if ((param_2 != 0) && (cVar1 = PlayerCharacter::sub(param_2), cVar1 == '\0')) {
    auStack_98[0] = 10;
    puVar2 = (undefined4 *)GetOrCreateObjectRefHandle_Safe(param_2,auStackX_10);
    uStack_90 = *puVar2;
    uStack_88 = param_3;
    uStack_80 = param_4;
    if (*(longlong *)(param_2 + 0xf8) == 0) {
      fStack_78 = 1.0;
    }
    else {
      fStack_78 = (float)FUN_1406ec620();
    }
    if (fStack_78 != 1.0) {
      puVar2 = (undefined4 *)FUN_1406ec690(*(undefined8 *)(param_2 + 0xf8));
      uStack_70 = *puVar2;
      uStack_68 = puVar2[1];
      uStack_60 = puVar2[2];
    }
    uStack_58 = param_5;
    uStack_50 = param_6;
    Character::sub(param_2,1);  // 14065571a
    FUN_1406595d0(param_1,auStack_98);
  }
  return;
}

