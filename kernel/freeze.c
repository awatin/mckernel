#include <kmsg.h>
#include <string.h>
#include <ihk/cpu.h>
#include <ihk/debug.h>
#include <cls.h>
#include <ihk/monitor.h>

extern int nmi_mode;
extern void mod_nmi_ctx(void *, void(*)());
extern void lapic_ack();
extern void __freeze();

void
freeze()
{
	struct ihk_os_cpu_monitor *monitor = cpu_local_var(monitor);

	monitor->status_bak = monitor->status;
	monitor->status = IHK_OS_MONITOR_KERNEL_FROZEN;
#ifdef POSTK_DEBUG_ARCH_DEP_82 /* Add cpu_pause() to freeze loop */
	while (monitor->status == IHK_OS_MONITOR_KERNEL_FROZEN) {
		cpu_halt();
		cpu_pause();
	}
#else /* POSTK_DEBUG_ARCH_DEP_82 */
	while (monitor->status == IHK_OS_MONITOR_KERNEL_FROZEN)
		cpu_halt();
#endif /* POSTK_DEBUG_ARCH_DEP_82 */
	monitor->status = monitor->status_bak;
}

long
freeze_thaw(void *nmi_ctx)
{
	struct ihk_os_cpu_monitor *monitor = cpu_local_var(monitor);

	if (nmi_mode == 1) {
		if (monitor->status != IHK_OS_MONITOR_KERNEL_FROZEN) {
#if 1
			mod_nmi_ctx(nmi_ctx, __freeze);
			return 1;
#else
			unsigned long flags;

			flags = cpu_disable_interrupt_save();
			monitor->status_bak = monitor->status;
			monitor->status = IHK_OS_MONITOR_KERNEL_FROZEN;
			lapic_ack();
			while (monitor->status == IHK_OS_MONITOR_KERNEL_FROZEN)
				cpu_halt();
			monitor->status = monitor->status_bak;
			cpu_restore_interrupt(flags);
#endif
		}
	}
	else if(nmi_mode == 2) {
		if (monitor->status == IHK_OS_MONITOR_KERNEL_FROZEN) {
			monitor->status = IHK_OS_MONITOR_KERNEL_THAW;
		}
	}
	return 0;
}
