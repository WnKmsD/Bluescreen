#include <windows.h>
#include <ntstatus.h>
#include <winternl.h>
#include <iostream>
using namespace std;
#pragma comment(lib, "ntdll.lib")

extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN OldValue);
extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask,
    PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);

int main()
{
    setlocale(LC_ALL, "chs");
    cout << "按任意键触发蓝屏...";
    system("pause>nul");
    BOOLEAN bl;
    ULONG Response;
    UNICODE_STRING ustr;
    RtlInitUnicodeString(&ustr, L"Error:Unknown Hard Error");
    RtlAdjustPrivilege(19, TRUE, FALSE, &bl);
    ULONGLONG n[4] = {(ULONGLONG)&ustr, 0xDEADDEAD, 0, 0};
    NtRaiseHardError(STATUS_STACK_OVERFLOW, 4, 1, n, 6, &Response);
}
