#include <nn/hac/KernelCapabilityUtil.h>
#include <sstream>
#include <iomanip>

std::string nn::hac::KernelCapabilityUtil::getMiscFlagAsString(nn::hac::kc::MiscFlags flag)
{
	std::stringstream ss;

	switch(flag)
	{
	case (nn::hac::kc::MISCFLAG_ENABLE_DEBUG):
		ss << "EnableDebug";
		break;
	case (nn::hac::kc::MISCFLAG_FORCE_DEBUG):
		ss << "ForceDebug";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)flag;
		break;
	}

	return ss.str();
}

std::string nn::hac::KernelCapabilityUtil::getMemMapPermAsString(nn::hac::kc::MemoryPerm type)
{
	std::stringstream ss;

	switch(type)
	{
	case (nn::hac::kc::MEM_RW):
		ss << "RW";
		break;
	case (nn::hac::kc::MEM_RO):
		ss << "RO";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)type;
		break;
	}

	return ss.str();
}

std::string nn::hac::KernelCapabilityUtil::getMemMapTypeAsString(nn::hac::kc::MappingType type)
{
	std::stringstream ss;

	switch(type)
	{
	case (nn::hac::kc::MAP_IO):
		ss << "Io";
		break;
	case (nn::hac::kc::MAP_STATIC):
		ss << "Static";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)type;
		break;
	}

	return ss.str();
}

std::string nn::hac::KernelCapabilityUtil::getSystemCallAsString(nn::hac::kc::SystemCall svc)
{
	std::stringstream ss;

	switch(svc)
	{
	case (nn::hac::kc::SVC_SET_HEAP_SIZE):
		ss << "SetHeapSize";
		break;
	case (nn::hac::kc::SVC_SET_MEMORY_PERMISSION):
		ss << "SetMemoryPermission";
		break;
	case (nn::hac::kc::SVC_SET_MEMORY_ATTRIBUTE):
		ss << "SetMemoryAttribute";
		break;
	case (nn::hac::kc::SVC_MAP_MEMORY):
		ss << "MapMemory";
		break;
	case (nn::hac::kc::SVC_UNMAP_MEMORY):
		ss << "UnmapMemory";
		break;
	case (nn::hac::kc::SVC_QUERY_MEMORY):
		ss << "QueryMemory";
		break;
	case (nn::hac::kc::SVC_EXIT_PROCESS):
		ss << "ExitProcess";
		break;
	case (nn::hac::kc::SVC_CREATE_THREAD):
		ss << "CreateThread";
		break;
	case (nn::hac::kc::SVC_START_THREAD):
		ss << "StartThread";
		break;
	case (nn::hac::kc::SVC_EXIT_THREAD):
		ss << "ExitThread";
		break;
	case (nn::hac::kc::SVC_SLEEP_THREAD):
		ss << "SleepThread";
		break;
	case (nn::hac::kc::SVC_GET_THREAD_PRIORITY):
		ss << "GetThreadPriority";
		break;
	case (nn::hac::kc::SVC_SET_THREAD_PRIORITY):
		ss << "SetThreadPriority";
		break;
	case (nn::hac::kc::SVC_GET_THREAD_CORE_MASK):
		ss << "GetThreadCoreMask";
		break;
	case (nn::hac::kc::SVC_SET_THREAD_CORE_MASK):
		ss << "SetThreadCoreMask";
		break;
	case (nn::hac::kc::SVC_GET_CURRENT_PROCESSOR_NUMBER):
		ss << "GetCurrentProcessorNumber";
		break;
	case (nn::hac::kc::SVC_SIGNAL_EVENT):
		ss << "SignalEvent";
		break;
	case (nn::hac::kc::SVC_CLEAR_EVENT):
		ss << "ClearEvent";
		break;
	case (nn::hac::kc::SVC_MAP_SHARED_MEMORY):
		ss << "MapSharedMemory";
		break;
	case (nn::hac::kc::SVC_UNMAP_SHARED_MEMORY):
		ss << "UnmapSharedMemory";
		break;
	case (nn::hac::kc::SVC_CREATE_TRANSFER_MEMORY):
		ss << "CreateTransferMemory";
		break;
	case (nn::hac::kc::SVC_CLOSE_HANDLE):
		ss << "CloseHandle";
		break;
	case (nn::hac::kc::SVC_RESET_SIGNAL):
		ss << "ResetSignal";
		break;
	case (nn::hac::kc::SVC_WAIT_SYNCHRONIZATION):
		ss << "WaitSynchronization";
		break;
	case (nn::hac::kc::SVC_CANCEL_SYNCHRONIZATION):
		ss << "CancelSynchronization";
		break;
	case (nn::hac::kc::SVC_ARBIRATE_LOCK):
		ss << "ArbitrateLock";
		break;
	case (nn::hac::kc::SVC_ARBIRATE_UNLOCK):
		ss << "ArbitrateUnlock";
		break;
	case (nn::hac::kc::SVC_WAIT_PROCESS_WIDE_KEY_ATOMIC):
		ss << "WaitProcessWideKeyAtomic";
		break;
	case (nn::hac::kc::SVC_SIGNAL_PROCESS_WIDE_KEY):
		ss << "SignalProcessWideKey";
		break;
	case (nn::hac::kc::SVC_GET_SYSTEM_TICK):
		ss << "GetSystemTick";
		break;
	case (nn::hac::kc::SVC_CONNECT_TO_NAMED_PORT):
		ss << "ConnectToNamedPort";
		break;
	case (nn::hac::kc::SVC_SEND_SYNC_REQUEST_LIGHT):
		ss << "SendSyncRequestLight";
		break;
	case (nn::hac::kc::SVC_SEND_SYNC_REQUEST):
		ss << "SendSyncRequest";
		break;
	case (nn::hac::kc::SVC_SEND_SYNC_REQUEST_WITH_USER_BUFFER):
		ss << "SendSyncRequestWithUserBuffer";
		break;
	case (nn::hac::kc::SVC_SEND_ASYNC_REQUEST_WITH_USER_BUFFER):
		ss << "SendAsyncRequestWithUserBuffer";
		break;
	case (nn::hac::kc::SVC_GET_PROCESS_ID):
		ss << "GetProcessId";
		break;
	case (nn::hac::kc::SVC_GET_THREAD_ID):
		ss << "GetThreadId";
		break;
	case (nn::hac::kc::SVC_BREAK):
		ss << "Break";
		break;
	case (nn::hac::kc::SVC_OUTPUT_DEBUG_STRING):
		ss << "OutputDebugString";
		break;
	case (nn::hac::kc::SVC_RETURN_FROM_EXCEPTION):
		ss << "ReturnFromException";
		break;
	case (nn::hac::kc::SVC_GET_INFO):
		ss << "GetInfo";
		break;
	case (nn::hac::kc::SVC_FLUSH_ENTIRE_DATA_CACHE):
		ss << "FlushEntireDataCache";
		break;
	case (nn::hac::kc::SVC_FLUSH_DATA_CACHE):
		ss << "FlushDataCache";
		break;
	case (nn::hac::kc::SVC_MAP_PHYSICAL_MEMORY):
		ss << "MapPhysicalMemory";
		break;
	case (nn::hac::kc::SVC_UNMAP_PHYSICAL_MEMORY):
		ss << "UnmapPhysicalMemory";
		break;
	case (nn::hac::kc::SVC_GET_FUTURE_THREAD_INFO):
		ss << "GetFutureThreadInfo";
		break;
	case (nn::hac::kc::SVC_GET_LAST_THREAD_INFO):
		ss << "GetLastThreadInfo";
		break;
	case (nn::hac::kc::SVC_GET_RESOURCE_LIMIT_LIMIT_VALUE):
		ss << "GetResourceLimitLimitValue";
		break;
	case (nn::hac::kc::SVC_GET_RESOURCE_LIMIT_CURRENT_VALUE):
		ss << "GetResourceLimitCurrentValue";
		break;
	case (nn::hac::kc::SVC_SET_THREAD_ACTIVITY):
		ss << "SetThreadActivity";
		break;
	case (nn::hac::kc::SVC_GET_THREAD_CONTEXT3):
		ss << "GetThreadContext3";
		break;
	case (nn::hac::kc::SVC_WAIT_FOR_ADDRESS):
		ss << "WaitForAddress";
		break;
	case (nn::hac::kc::SVC_SIGNAL_TO_ADDRESS):
		ss << "SignalToAddress";
		break;
	case (nn::hac::kc::SVC_SYNCHRONIZE_PREEMPTION_STATE):
		ss << "SynchronizePreemptionState";
		break;
	case (nn::hac::kc::SVC_DUMP_INFO):
		ss << "DumpInfo";
		break;
	case (nn::hac::kc::SVC_DUMP_INFO_NEW):
		ss << "DumpInfoNew";
		break;
	case (nn::hac::kc::SVC_CREATE_SESSION):
		ss << "CreateSession";
		break;
	case (nn::hac::kc::SVC_ACCEPT_SESSION):
		ss << "AcceptSession";
		break;
	case (nn::hac::kc::SVC_REPLY_AND_RECEIVE_LIGHT):
		ss << "ReplyAndReceiveLight";
		break;
	case (nn::hac::kc::SVC_REPLY_AND_RECEIVE):
		ss << "ReplyAndReceive";
		break;
	case (nn::hac::kc::SVC_REPLY_AND_RECEIVE_WITH_USER_BUFFER):
		ss << "ReplyAndReceiveWithUserBuffer";
		break;
	case (nn::hac::kc::SVC_CREATE_EVENT):
		ss << "CreateEvent";
		break;
	case (nn::hac::kc::SVC_MAP_PHYSICAL_MEMORY_UNSAFE):
		ss << "MapPhysicalMemoryUnsafe";
		break;
	case (nn::hac::kc::SVC_UNMAP_PHYSICAL_MEMORY_UNSAFE):
		ss << "UnmapPhysicalMemoryUnsafe";
		break;
	case (nn::hac::kc::SVC_SET_UNSAFE_LIMIT):
		ss << "SetUnsafeLimit";
		break;
	case (nn::hac::kc::SVC_CREATE_CODE_MEMORY):
		ss << "CreateCodeMemory";
		break;
	case (nn::hac::kc::SVC_CONTROL_CODE_MEMORY):
		ss << "ControlCodeMemory";
		break;
	case (nn::hac::kc::SVC_SLEEP_SYSTEM):
		ss << "SleepSystem";
		break;
	case (nn::hac::kc::SVC_READ_WRITE_REGISTER):
		ss << "ReadWriteRegister";
		break;
	case (nn::hac::kc::SVC_SET_PROCESS_ACTIVITY):
		ss << "SetProcessActivity";
		break;
	case (nn::hac::kc::SVC_CREATE_SHARED_MEMORY):
		ss << "CreateSharedMemory";
		break;
	case (nn::hac::kc::SVC_MAP_TRANSFER_MEMORY):
		ss << "MapTransferMemory";
		break;
	case (nn::hac::kc::SVC_UNMAP_TRANSFER_MEMORY):
		ss << "UnmapTransferMemory";
		break;
	case (nn::hac::kc::SVC_CREATE_INTERRUPT_EVENT):
		ss << "CreateInterruptEvent";
		break;
	case (nn::hac::kc::SVC_QUERY_PHYSICAL_ADDRESS):
		ss << "QueryPhysicalAddress";
		break;
	case (nn::hac::kc::SVC_QUERY_IO_MAPPING):
		ss << "QueryIoMapping";
		break;
	case (nn::hac::kc::SVC_CREATE_DEVICE_ADDRESS_SPACE):
		ss << "CreateDeviceAddressSpace";
		break;
	case (nn::hac::kc::SVC_ATTACH_DEVICE_ADDRESS_SPACE):
		ss << "AttachDeviceAddressSpace";
		break;
	case (nn::hac::kc::SVC_DETACH_DEVICE_ADDRESS_SPACE):
		ss << "DetachDeviceAddressSpace";
		break;
	case (nn::hac::kc::SVC_MAP_DEVICE_ADDRESS_SPACE_BY_FORCE):
		ss << "MapDeviceAddressSpaceByForce";
		break;
	case (nn::hac::kc::SVC_MAP_DEVICE_ADDRESS_SPACE_ALIGNED):
		ss << "MapDeviceAddressSpaceAligned";
		break;
	case (nn::hac::kc::SVC_MAP_DEVICE_ADDRESS_SPACE):
		ss << "MapDeviceAddressSpace";
		break;
	case (nn::hac::kc::SVC_UNMAP_DEVICE_ADDRESS_SPACE):
		ss << "UnmapDeviceAddressSpace";
		break;
	case (nn::hac::kc::SVC_INVALIDATE_PROCESS_DATA_CACHE):
		ss << "InvalidateProcessDataCache";
		break;
	case (nn::hac::kc::SVC_STORE_PROCESS_DATA_CACHE):
		ss << "StoreProcessDataCache";
		break;
	case (nn::hac::kc::SVC_FLUSH_PROCESS_DATA_CACHE):
		ss << "FlushProcessDataCache";
		break;
	case (nn::hac::kc::SVC_DEBUG_ACTIVE_PROCESS):
		ss << "DebugActiveProcess";
		break;
	case (nn::hac::kc::SVC_BREAK_DEBUG_PROCESS):
		ss << "BreakDebugProcess";
		break;
	case (nn::hac::kc::SVC_TERMINATE_DEBUG_PROCESS):
		ss << "TerminateDebugProcess";
		break;
	case (nn::hac::kc::SVC_GET_DEBUG_EVENT):
		ss << "GetDebugEvent";
		break;
	case (nn::hac::kc::SVC_CONTINUE_DEBUG_EVENT):
		ss << "ContinueDebugEvent";
		break;
	case (nn::hac::kc::SVC_GET_PROCESS_LIST):
		ss << "GetProcessList";
		break;
	case (nn::hac::kc::SVC_GET_THREAD_LIST):
		ss << "GetThreadList";
		break;
	case (nn::hac::kc::SVC_GET_DEBUG_THREAD_CONTEXT):
		ss << "GetDebugThreadContext";
		break;
	case (nn::hac::kc::SVC_SET_DEBUG_THREAD_CONTEXT):
		ss << "SetDebugThreadContext";
		break;
	case (nn::hac::kc::SVC_QUERY_DEBUG_PROCESS_MEMORY):
		ss << "QueryDebugProcessMemory";
		break;
	case (nn::hac::kc::SVC_READ_DEBUG_PROCESS_MEMORY):
		ss << "ReadDebugProcessMemory";
		break;
	case (nn::hac::kc::SVC_WRITE_DEBUG_PROCESS_MEMORY):
		ss << "WriteDebugProcessMemory";
		break;
	case (nn::hac::kc::SVC_SET_HARDWARE_BREAK_POINT):
		ss << "SetHardwareBreakPoint";
		break;
	case (nn::hac::kc::SVC_GET_DEBUG_THREAD_PARAM):
		ss << "GetDebugThreadParam";
		break;
	case (nn::hac::kc::SVC_GET_SYSTEM_INFO):
		ss << "GetSystemInfo";
		break;
	case (nn::hac::kc::SVC_CREATE_PORT):
		ss << "CreatePort";
		break;
	case (nn::hac::kc::SVC_MANAGE_NAMED_PORT):
		ss << "ManageNamedPort";
		break;
	case (nn::hac::kc::SVC_CONNECT_TO_PORT):
		ss << "ConnectToPort";
		break;
	case (nn::hac::kc::SVC_SET_PROCESS_MEMORY_PERMISSION):
		ss << "SetProcessMemoryPermission";
		break;
	case (nn::hac::kc::SVC_MAP_PROCESS_MEMORY):
		ss << "MapProcessMemory";
		break;
	case (nn::hac::kc::SVC_UNMAP_PROCESS_MEMORY):
		ss << "UnmapProcessMemory";
		break;
	case (nn::hac::kc::SVC_QUERY_PROCESS_MEMORY):
		ss << "QueryProcessMemory";
		break;
	case (nn::hac::kc::SVC_MAP_PROCESS_CODE_MEMORY):
		ss << "MapProcessCodeMemory";
		break;
	case (nn::hac::kc::SVC_UNMAP_PROCESS_CODE_MEMORY):
		ss << "UnmapProcessCodeMemory";
		break;
	case (nn::hac::kc::SVC_CREATE_PROCESS):
		ss << "CreateProcess";
		break;
	case (nn::hac::kc::SVC_START_PROCESS):
		ss << "StartProcess";
		break;
	case (nn::hac::kc::SVC_TERMINATE_PROCESS):
		ss << "TerminateProcess";
		break;
	case (nn::hac::kc::SVC_GET_PROCESS_INFO):
		ss << "GetProcessInfo";
		break;
	case (nn::hac::kc::SVC_CREATE_RESOURCE_LIMIT):
		ss << "CreateResourceLimit";
		break;
	case (nn::hac::kc::SVC_SET_RESOURCE_LIMIT_LIMIT_VALUE):
		ss << "SetResourceLimitLimitValue";
		break;
	case (nn::hac::kc::SVC_CALL_SECURE_MONITOR):
		ss << "CallSecureMonitor";
		break;
	default:
		ss << "svc" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)svc;
		break;
	}

	return ss.str();
}