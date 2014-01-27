#include "boxrunner.h"

using namespace Judger;

res_t BoxRunner::probe(const sandbox_t* psbox, probe_t key) {
    switch (key) {
        case P_ELAPSED:
            return ts2ms(psbox->stat.elapsed);
        case P_CPU:
            return ts2ms(psbox->stat.cpu_info.clock);
        case P_MEMORY:
            return psbox->stat.mem_info.vsize_peak / 1024;
        default:
            break;
    }
    return 0;
}

void BoxRunner::policy_setup(minisbox_t* pmsb)/////this Function is not complete
{
    assert(pmsb);

    const int16_t ban_list[] =
    {
//-----------------------------------------------------------------//
        -1,
    };
    /* initialize table of system call rules */
    int sc, i = 0;
    for (sc = 0; sc <= INT16_MAX; sc++)
    {
        pmsb->sc_table[sc] = _KILL_RF;
    }
    while ((sc = sc_safe[i++]) >= 0)
    {
        pmsb->sc_table[sc] = _CONT;
    }
    /* override the default policy of the sandbox */
    pmsb->default_policy = pmsb->sbox.ctrl.policy;
    pmsb->default_policy.entry = (pmsb->default_policy.entry) ?: \
        (void*)sandbox_default_policy;
    pmsb->sbox.ctrl.policy = (policy_t){(void*)policy, (long)pmsb};
}

void BoxRunner::policy(const policy_t* pp, const event_t* pe, action_t* pa)
{
    assert(pp && pe && pa);
    const minisbox_t* pmsb = (const minisbox_t*)pp->data;
    /* handle SYSCALL/SYSRET events with local rules */
    if ((pe->type == S_EVENT_SYSCALL) || (pe->type == S_EVENT_SYSRET))
    {
        const syscall_t scinfo = *(const syscall_t*)&(pe->data._SYSCALL.scinfo);
        pmsb->sc_table[sc2idx(scinfo)](&pmsb->sbox, pe, pa);
        return;
    }
    /* bypass other events to the default poicy */
    ((policy_entry_t)pmsb->default_policy.entry)(&pmsb->default_policy, pe, pa);
}

action_t* BoxRunner::_CONT(const sandbox_t* psbox, const event_t* pe, action_t* pa)
{
    *pa = (action_t){S_ACTION_CONT}; /* continue */
    return pa;
}

action_t* BoxRunner::_KILL_RF(const sandbox_t* psbox, const event_t* pe, action_t* pa)
{
    *pa = (action_t){S_ACTION_KILL, {{S_RESULT_RF}}}; /* restricted func. */
    return pa;
}