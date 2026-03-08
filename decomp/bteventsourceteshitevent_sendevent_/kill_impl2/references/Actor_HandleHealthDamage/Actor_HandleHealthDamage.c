// 1406b9950
void UndefinedFunction_1406b9950(longlong *param_1,undefined8 param_2,undefined4 param_3)

{
  char cVar1;
  float fVar2;

  cVar1 = (**(code **)(*param_1 + 0x4c8))(param_1,0);
  if (cVar1 == '\0') {
    fVar2 = (float)(**(code **)(param_1[0x17] + 8))(param_1 + 0x17,0x18);
    cVar1 = func_0x0001406bc4a0(param_1,param_2,fVar2);
    if ((cVar1 == '\0') && (fVar2 <= 0.0)) {
      Actor::Kill_impl2(param_1,param_2,param_3,1,0);  // 1406b99bb
    }
  }
  return;
}

