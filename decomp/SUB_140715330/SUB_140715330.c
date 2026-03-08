// 140715330
void UndefinedFunction_140715330(longlong param_1,undefined4 param_2)

{
  if (*(longlong *)(param_1 + 8) != 0) {
    *(undefined4 *)(*(longlong *)(param_1 + 8) + 0x2b8) = param_2;
  }
  return;
}

