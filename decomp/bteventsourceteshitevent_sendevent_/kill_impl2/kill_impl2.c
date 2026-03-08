// 140664f80
void Actor::Kill_impl2(longlong param_1,longlong param_2,undefined4 param_3,undefined1 param_4,
                      undefined1 param_5)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 auStackX_8 [8];

  if ((*(longlong *)(param_1 + 0xf8) == 0) || (cVar1 = ActorProcess::sub(), cVar1 == '\0')) {
    uVar2 = gNullRefHandleId;
    if (param_2 != 0) {
      puVar3 = (undefined4 *)GetOrCreateObjectRefHandle_Safe(param_2,auStackX_8);
      uVar2 = *puVar3;
    }
    *(undefined4 *)(param_1 + 0x108) = uVar2;
    FUN_140655640(gBSTaskPool,param_1,param_3,0,param_4,param_5);
  }
  return;
}

