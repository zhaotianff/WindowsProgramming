#pragma once

/*
*   0x00 = 	SystemBasicInformation,  	all
	0x01	SystemProcessorInformation	all
	0x02	SystemPerformanceInformation	all
	0x03	SystemTimeOfDayInformation	all
	0x04	SystemPathInformation	all
	0x05	SystemProcessInformation	all
	0x06	SystemCallCountInformation	all
	0x07	SystemDeviceInformation	all
	0x08	SystemProcessorPerformanceInformation	all
	0x09	SystemFlagsInformation	all
	0x0A	SystemCallTimeInformation	all
	0x0B	SystemModuleInformation	all
	0x0C	SystemLocksInformation	all
	0x0D	SystemStackTraceInformation	all
	0x0E	SystemPagedPoolInformation	all
	0x0F	SystemNonPagedPoolInformation	all
	0x10	SystemHandleInformation	all
	0x11	SystemObjectInformation	all
	0x12	SystemPageFileInformation	all
	0x13	SystemVdmInstemulInformation	all
	0x14	SystemVdmBopInformation	all
	0x15	SystemFileCacheInformation	all
	0x16	SystemPoolTagInformation	3.50 and higher
	0x17	SystemSpare1Information	3.50 only	supposed name
	SystemInterruptInformation	3.51 and higher
	0x18	SystemSpare2Information	3.50 only	supposed name
	SystemDpcBehaviorInformation	3.51 and higher
	0x19	SystemSpare3Information	3.50 to 3.51
	SystemFullMemoryInformation	4.0 and higher
	0x1A	SystemSpare4Information	3.50 only	supposed name
	SystemLoadGdiDriverInformation	3.51 and higher
	0x1B	SystemSpare5Information	3.50 only	supposed name
	SystemUnloadGdiDriverInformation	3.51 and higher
	0x1C	SystemTimeAdjustmentInformation	3.50 and higher
	0x1D	SystemSpare6Information	3.50 to 3.51
	SystemSummaryMemoryInformation	4.0 and higher
	0x1E	SystemNextEventIdInformation	3.50 to 4.0
	unknown	5.0 only
	SystemMirrorMemoryInformation	5.1 and higher
	0x1F	SystemEventIdsInformation	3.50 to 4.0
	unknown	5.0 to 5.2
	SystemPerformanceTraceInformation	6.0 and higher
	0x20	SystemCrashDumpInformation	3.50 to 5.0
	SystemObsolete0	5.1 and higher
	0x21	SystemExceptionInformation	3.50 and higher
	0x22	SystemCrashDumpStateInformation	3.50 and higher
	0x23	SystemKernelDebuggerInformation	3.50 and higher
	0x24	SystemContextSwitchInformation	3.50 and higher
	0x25	SystemRegistryQuotaInformation	3.51 and higher
	0x26	SystemExtendServiceTableInformation	3.51 and higher
	0x27	SystemPrioritySeperation	3.51 and higher
	0x28	SystemPlugPlayBusInformation	3.51 to 4.0
	unknown	5.0 only
	SystemVerifierAddDriverInformation	5.1 and higher
	0x29	SystemDockInformation	3.51 to 4.0
	unknown	5.0 only
	SystemVerifierRemoveDriverInformation	5.1 and higher
	0x2A	SystemPowerInformation	3.51 to 5.0
	SystemProcessorIdleInformation	5.1 and higher
	0x2B	SystemProcessorSpeedInformation	3.51 to 4.0
	SystemLegacyDriverInformation	5.0 and higher
	0x2C	SystemCurrentTimeZoneInformation	4.0 and higher
	0x2D	SystemLookasideInformation	4.0 and higher
	0x2E	SystemTimeSlipNotification	5.0 and higher
	0x2F	SystemSessionCreate	5.0 and higher
	0x30	SystemSessionDetach	5.0 and higher
	0x31	SystemSessionInformation	5.0 and higher
	0x32	SystemRangeStartInformation	5.0 and higher
	0x33	SystemVerifierInformation	5.0 and higher
	0x34	SystemVerifierThunkExtend	5.0 and higher
	0x35	SystemSessionProcessInformation	5.0 and higher
	0x36	SystemObjectSecurityMode	late 5.0 only	later as 0x46
	SystemLoadGdiDriverInSystemSpace	5.1 and higher
	0x37	unknown	late 5.0 only	later as 0x47
	SystemNumaProcessorMap	5.1 and higher
	0x38	SystemPrefetcherInformation	5.1 and higher
	0x39	SystemExtendedProcessInformation	5.1 and higher
	0x3A	SystemRecommendedSharedDataAlignment	5.1 and higher
	0x3B	SystemComPlusPackage	5.1 and higher
	0x3C	SystemNumaAvailableMemory	5.1 and higher
	0x3D	SystemProcessorPowerInformation	5.1 and higher
	0x3E	SystemEmulationBasicInformation	5.1 and higher
	0x3F	SystemEmulationProcessorInformation	5.1 and higher
	0x40	SystemExtendedHandleInformation	5.1 and higher
	0x41	SystemLostDelayedWriteInformation	5.1 and higher
	0x42	unknown	late 5.1 only
	SystemBigPoolInformation	5.2 and higher
	0x43	SystemSessionPoolTagInformation	5.2 and higher
	0x44	SystemSessionMappedViewInformation	5.2 and higher
	0x45	SystemHotpatchInformation	late 5.1 and higher
	0x46	SystemObjectSecurityMode	late 5.1 and higher	earlier as 0x36
	0x47	unknown	late 5.1 only	earlier as 0x37
	SystemWatchdogTimerHandler	5.2 and higher
	0x48	SystemWatchdogTimerInformation	5.2 and higher
	0x49	SystemLogicalProcessorInformation	very late 5.1 and higher
	0x4A	SystemWow64SharedInformationObsolete	late 5.2 and higher
	0x4B	SystemRegisterFirmwareTableInformationHandler	late 5.2 and higher
	0x4C	SystemFirmwareTableInformation	late 5.2 and higher
	0x4D	SystemModuleInformationEx	6.0 and higher
	0x4E	SystemVerifierTriageInformation	6.0 and higher
	0x4F	SystemSuperfetchInformation	6.0 and higher
	0x50	SystemMemoryListInformation	6.0 and higher
	0x51	SystemFileCacheInformationEx	late 5.2 and higher
	0x52	SystemThreadPriorityClientIdInformation	6.0 and higher
	0x53	SystemProcessorIdleCycleTimeInformation	6.0 and higher
	0x54	SystemVerifierCancellationInformation	6.0 and higher
	0x55	SystemProcessorPowerInformationEx	6.0 and higher
	0x56	SystemRefTraceInformation	6.0 and higher
	0x57	SystemSpecialPoolInformation	6.0 and higher
	0x58	SystemProcessIdInformation	6.0 and higher
	0x59	SystemErrorPortInformation	6.0 and higher
	0x5A	SystemBootEnvironmentInformation	6.0 and higher
	0x5B	SystemHypervisorInformation	6.0 and higher
	0x5C	SystemVerifierInformationEx	6.0 and higher
	0x5D	SystemTimeZoneInformation	6.0 and higher
	0x5E	SystemImageFileExecutionOptionsInformation	6.0 and higher
	0x5F	SystemCoverageInformation	6.0 and higher
	0x60	SystemPrefetchPatchInformation	6.0 and higher
	0x61	SystemVerifierFaultsInformation	6.0 and higher
	0x62	SystemSystemPartitionInformation	6.0 and higher
	0x63	SystemSystemDiskInformation	6.0 and higher
	0x64	SystemProcessorPerformanceDistribution	6.0 and higher
	0x65	SystemNumaProximityNodeInformation	6.0 and higher
	0x66	SystemDynamicTimeZoneInformation	6.0 and higher
	0x67	SystemCodeIntegrityInformation	6.0 and higher
	0x68	SystemProcessorMicrocodeUpdateInformation	6.0 and higher
	0x69	SystemProcessorBrandString	late 6.0 and higher
	0x6A	SystemVirtualAddressInformation	late 6.0 and higher
	0x6B	SystemLogicalProcessorAndGroupInformation	6.1 and higher
	0x6C	SystemProcessorCycleTimeInformation	6.1 and higher
	0x6D	SystemStoreInformation	6.1 and higher
	0x6E	SystemRegistryAppendString	6.1 and higher
	0x6F	SystemAitSamplingValue	6.1 and higher
	0x70	SystemVhdBootInformation	6.1 and higher
	0x71	SystemCpuQuotaInformation	6.1 and higher
	0x72	SystemNativeBasicInformation	6.1 and higher
	0x73	SystemErrorPortTimeouts	6.1 and higher
	0x74	SystemLowPriorityIoInformation	6.1 and higher
	0x75	SystemBootEntropyInformation	6.1 and higher
	0x76	SystemVerifierCountersInformation	6.1 and higher
	0x77	SystemPagedPoolInformationEx	6.1 and higher
	0x78	SystemSystemPtesInformationEx	6.1 and higher
	0x79	SystemNodeDistanceInformation	6.1 and higher
	0x7A	SystemAcpiAuditInformation	6.1 and higher
	0x7B	SystemBasicPerformanceInformation	6.1 and higher
	0x7C	SystemQueryPerformanceCounterInformation	late 6.1 and higher
	0x7D	SystemSessionBigPoolInformation	6.2 and higher
	0x7E	SystemBootGraphicsInformation	6.2 and higher
	0x7F	SystemScrubPhysicalMemoryInformation	6.2 and higher
	0x80	SystemBadPageInformation	6.2 and higher
	0x81	SystemProcessorProfileControlArea	6.2 and higher
	0x82	SystemCombinePhysicalMemoryInformation	6.2 and higher
	0x83	SystemEntropyInterruptTimingInformation	6.2 and higher
	0x84	SystemConsoleInformation	6.2 and higher
	0x85	SystemPlatformBinaryInformation	6.2 and higher
	0x86	SystemThrottleNotificationInformation	6.2 only
	SystemPolicyInformation	6.3 and higher
	0x87	SystemHypervisorProcessorCountInformation	6.2 and higher
	0x88	SystemDeviceDataInformation	6.2 and higher
	0x89	SystemDeviceDataEnumerationInformation	6.2 and higher
	0x8A	SystemMemoryTopologyInformation	6.2 and higher
	0x8B	SystemMemoryChannelInformation	6.2 and higher
	0x8C	SystemBootLogoInformation	6.2 and higher
	0x8D	SystemProcessorPerformanceInformationEx	6.2 and higher
	0x8E	SystemSpare0	6.2 to 1511
	SystemCriticalProcessErrorLogInformation	1607 and higher
	0x8F	SystemSecureBootPolicyInformation	6.2 and higher
	0x90	SystemPageFileInformationEx	6.2 and higher
	0x91	SystemSecureBootInformation	6.2 and higher
	0x92	SystemEntropyInterruptTimingRawInformation	6.2 and higher
	0x93	SystemPortableWorkspaceEfiLauncherInformation	6.2 and higher
	0x94	SystemFullProcessInformation	6.2 and higher
	0x95	SystemKernelDebuggerInformationEx	6.3 and higher
	0x96	SystemBootMetadataInformation	6.3 and higher
	0x97	SystemSoftRebootInformation	6.3 and higher
	0x98	SystemElamCertificateInformation	6.3 and higher
	0x99	SystemOfflineDumpConfigInformation	6.3 and higher
	0x9A	SystemProcessorFeaturesInformation	6.3 and higher
	0x9B	SystemRegistryReconciliationInformation	6.3 and higher
	0x9C	SystemEdidInformation	6.3 and higher
	0x9D	SystemManufacturingInformation	10.0 and higher
	0x9E	SystemEnergyEstimationConfigInformation	10.0 and higher
	0x9F	SystemHypervisorDetailInformation	10.0 and higher
	0xA0	SystemProcessorCycleStatsInformation	10.0 and higher
	0xA1	SystemVmGenerationCountInformation	10.0 and higher
	0xA2	SystemTrustedPlatformModuleInformation	10.0 and higher
	0xA3	SystemKernelDebuggerFlags	10.0 and higher
	0xA4	SystemCodeIntegrityPolicyInformation	10.0 and higher
	0xA5	SystemIsolatedUserModeInformation	10.0 and higher
	0xA6	SystemHardwareSecurityTestInterfaceResultsInformation	10.0 and higher
	0xA7	SystemSingleModuleInformation	10.0 and higher
	0xA8	SystemAllowedCpuSetsInformation	10.0 and higher
	0xA9	SystemDmaProtectionInformation	10.0 and higher
	0xAA	SystemInterruptCpuSetsInformation	10.0 and higher
	0xAB	SystemSecureBootPolicyFullInformation	10.0 and higher
	0xAC	SystemCodeIntegrityPolicyFullInformation	10.0 and higher
	0xAD	SystemAffinitizedInterruptProcessorInformation	10.0 and higher
	0xAE	SystemRootSiloInformation	10.0 and higher
	0xAF	SystemCpuSetInformation	10.0 and higher
	0xB0	SystemCpuSetTagInformation	10.0 and higher
	0xB1	SystemWin32WerStartCallout	1511 and higher
	0xB2	SystemSecureKernelProfileInformation	1511 and higher
	0xB3	SystemCodeIntegrityPlatformManifestInformation	1607 and higher
	0xB4	SystemInterruptSteeringInformation	1607 and higher
	0xB5	SystemSuppportedProcessorArchitectures	1607 and higher
	0xB6	SystemMemoryUsageInformation	1607 and higher
	0xB7	SystemCodeIntegrityCertificateInformation	1607 and higher
	0xB8	SystemPhysicalMemoryInformation	1703 and higher
	0xB9	SystemControlFlowTransition	1703 and higher
	0xBA	SystemKernelDebuggingAllowed	1703 and higher
	0xBB	SystemActivityModerationExeState	1703 and higher
	0xBC	SystemActivityModerationUserSettings	1703 and higher
	0xBD	SystemCodeIntegrityPoliciesFullInformation	1703 and higher
	0xBE	SystemCodeIntegrityUnlockInformation	1703 and higher
	0xBF	SystemIntegrityQuotaInformation	1703 and higher
	0xC0	SystemFlushInformation	1703 and higher
	0xC1	SystemProcessorIdleMaskInformation	1709 and higher
	0xC2	SystemSecureDumpEncryptionInformation	1709 and higher
	0xC3	SystemWriteConstraintInformation	1709 and higher
	0xC4	SystemKernelVaShadowInformation	1803 and higher
	0xC5	SystemHypervisorSharedPageInformation	1803 and higher
	0xC6	SystemFirmwareBootPerformanceInformation	1803 and higher
	0xC7	SystemCodeIntegrityVerificationInformation	1803 and higher
	0xC8	SystemFirmwarePartitionInformation	1803 and higher
	0xC9	SystemSpeculationControlInformation	1803 and higher
	0xCA	SystemDmaGuardPolicyInformation	1803 and higher
	0xCB	SystemEnclaveLaunchControlInformation	1803 and higher
	0xCC	SystemWorkloadAllowedCpuSetsInformation	1809 and higher
	0xCD	SystemCodeIntegrityUnlockModeInformation	1809 and higher
	0xCE	SystemLeapSecondInformation	1809 and higher
	0xCF	SystemFlags2Information	1809 and higher
	0xD0	SystemSecurityModelInformation	1903 and higher
	0xD1	SystemCodeIntegritySyntheticCacheInformation	1903 and higher
	0xD2	SystemFeatureConfigurationInformation	2004 and higher
	0xD3	SystemFeatureConfigurationSectionInformation	2004 and higher
	0xD4	SystemFeatureUsageSubscriptionInformation	2004 and higher
	0xD5	SystemSecureSpeculationControlInformation	2004 and higher
*/