#include "wrapper.h"

// Static wrappers

bool atomic_cas__extern(atomic_t *target, atomic_val_t old_value, atomic_val_t new_value) { return atomic_cas(target, old_value, new_value); }
bool atomic_ptr_cas__extern(atomic_ptr_t *target, atomic_ptr_val_t old_value, atomic_ptr_val_t new_value) { return atomic_ptr_cas(target, old_value, new_value); }
atomic_val_t atomic_add__extern(atomic_t *target, atomic_val_t value) { return atomic_add(target, value); }
atomic_val_t atomic_sub__extern(atomic_t *target, atomic_val_t value) { return atomic_sub(target, value); }
atomic_val_t atomic_inc__extern(atomic_t *target) { return atomic_inc(target); }
atomic_val_t atomic_dec__extern(atomic_t *target) { return atomic_dec(target); }
atomic_val_t atomic_get__extern(const atomic_t *target) { return atomic_get(target); }
atomic_ptr_val_t atomic_ptr_get__extern(const atomic_ptr_t *target) { return atomic_ptr_get(target); }
atomic_val_t atomic_set__extern(atomic_t *target, atomic_val_t value) { return atomic_set(target, value); }
atomic_ptr_val_t atomic_ptr_set__extern(atomic_ptr_t *target, atomic_ptr_val_t value) { return atomic_ptr_set(target, value); }
atomic_val_t atomic_clear__extern(atomic_t *target) { return atomic_clear(target); }
atomic_ptr_val_t atomic_ptr_clear__extern(atomic_ptr_t *target) { return atomic_ptr_clear(target); }
atomic_val_t atomic_or__extern(atomic_t *target, atomic_val_t value) { return atomic_or(target, value); }
atomic_val_t atomic_xor__extern(atomic_t *target, atomic_val_t value) { return atomic_xor(target, value); }
atomic_val_t atomic_and__extern(atomic_t *target, atomic_val_t value) { return atomic_and(target, value); }
atomic_val_t atomic_nand__extern(atomic_t *target, atomic_val_t value) { return atomic_nand(target, value); }
bool atomic_test_bit__extern(const atomic_t *target, int bit) { return atomic_test_bit(target, bit); }
bool atomic_test_and_clear_bit__extern(atomic_t *target, int bit) { return atomic_test_and_clear_bit(target, bit); }
bool atomic_test_and_set_bit__extern(atomic_t *target, int bit) { return atomic_test_and_set_bit(target, bit); }
void atomic_clear_bit__extern(atomic_t *target, int bit) { atomic_clear_bit(target, bit); }
void atomic_set_bit__extern(atomic_t *target, int bit) { atomic_set_bit(target, bit); }
void atomic_set_bit_to__extern(atomic_t *target, int bit, bool val) { atomic_set_bit_to(target, bit, val); }
bool is_power_of_two__extern(unsigned int x) { return is_power_of_two(x); }
int64_t arithmetic_shift_right__extern(int64_t value, uint8_t shift) { return arithmetic_shift_right(value, shift); }
void bytecpy__extern(void *dst, const void *src, size_t size) { bytecpy(dst, src, size); }
void byteswp__extern(void *a, void *b, size_t size) { byteswp(a, b, size); }
uint8_t bcd2bin__extern(uint8_t bcd) { return bcd2bin(bcd); }
uint8_t bin2bcd__extern(uint8_t bin) { return bin2bcd(bin); }
void sys_dlist_init__extern(sys_dlist_t *list) { sys_dlist_init(list); }
void sys_dnode_init__extern(sys_dnode_t *node) { sys_dnode_init(node); }
bool sys_dnode_is_linked__extern(const sys_dnode_t *node) { return sys_dnode_is_linked(node); }
bool sys_dlist_is_head__extern(sys_dlist_t *list, sys_dnode_t *node) { return sys_dlist_is_head(list, node); }
bool sys_dlist_is_tail__extern(sys_dlist_t *list, sys_dnode_t *node) { return sys_dlist_is_tail(list, node); }
bool sys_dlist_is_empty__extern(sys_dlist_t *list) { return sys_dlist_is_empty(list); }
bool sys_dlist_has_multiple_nodes__extern(sys_dlist_t *list) { return sys_dlist_has_multiple_nodes(list); }
sys_dnode_t * sys_dlist_peek_head__extern(sys_dlist_t *list) { return sys_dlist_peek_head(list); }
sys_dnode_t * sys_dlist_peek_head_not_empty__extern(sys_dlist_t *list) { return sys_dlist_peek_head_not_empty(list); }
sys_dnode_t * sys_dlist_peek_next_no_check__extern(sys_dlist_t *list, sys_dnode_t *node) { return sys_dlist_peek_next_no_check(list, node); }
sys_dnode_t * sys_dlist_peek_next__extern(sys_dlist_t *list, sys_dnode_t *node) { return sys_dlist_peek_next(list, node); }
sys_dnode_t * sys_dlist_peek_prev_no_check__extern(sys_dlist_t *list, sys_dnode_t *node) { return sys_dlist_peek_prev_no_check(list, node); }
sys_dnode_t * sys_dlist_peek_prev__extern(sys_dlist_t *list, sys_dnode_t *node) { return sys_dlist_peek_prev(list, node); }
sys_dnode_t * sys_dlist_peek_tail__extern(sys_dlist_t *list) { return sys_dlist_peek_tail(list); }
void sys_dlist_append__extern(sys_dlist_t *list, sys_dnode_t *node) { sys_dlist_append(list, node); }
void sys_dlist_prepend__extern(sys_dlist_t *list, sys_dnode_t *node) { sys_dlist_prepend(list, node); }
void sys_dlist_insert__extern(sys_dnode_t *successor, sys_dnode_t *node) { sys_dlist_insert(successor, node); }
void sys_dlist_insert_at__extern(sys_dlist_t *list, sys_dnode_t *node, int (*cond) (sys_dnode_t *node, void *data), void *data) { sys_dlist_insert_at(list, node, cond, data); }
void sys_dlist_remove__extern(sys_dnode_t *node) { sys_dlist_remove(node); }
sys_dnode_t * sys_dlist_get__extern(sys_dlist_t *list) { return sys_dlist_get(list); }
size_t sys_dlist_len__extern(sys_dlist_t *list) { return sys_dlist_len(list); }
struct rbnode * rb_get_min__extern(struct rbtree *tree) { return rb_get_min(tree); }
struct rbnode * rb_get_max__extern(struct rbtree *tree) { return rb_get_max(tree); }
void rb_walk__extern(struct rbtree *tree, rb_visit_t visit_fn, void *cookie) { rb_walk(tree, visit_fn, cookie); }
void sys_slist_init__extern(sys_slist_t *list) { sys_slist_init(list); }
sys_snode_t * z_snode_next_peek__extern(sys_snode_t *node) { return z_snode_next_peek(node); }
void z_snode_next_set__extern(sys_snode_t *parent, sys_snode_t *child) { z_snode_next_set(parent, child); }
void z_slist_head_set__extern(sys_slist_t *list, sys_snode_t *node) { z_slist_head_set(list, node); }
void z_slist_tail_set__extern(sys_slist_t *list, sys_snode_t *node) { z_slist_tail_set(list, node); }
sys_snode_t * sys_slist_peek_head__extern(sys_slist_t *list) { return sys_slist_peek_head(list); }
sys_snode_t * sys_slist_peek_tail__extern(sys_slist_t *list) { return sys_slist_peek_tail(list); }
bool sys_slist_is_empty__extern(sys_slist_t *list) { return sys_slist_is_empty(list); }
sys_snode_t * sys_slist_peek_next_no_check__extern(sys_snode_t *node) { return sys_slist_peek_next_no_check(node); }
sys_snode_t * sys_slist_peek_next__extern(sys_snode_t *node) { return sys_slist_peek_next(node); }
void sys_slist_prepend__extern(sys_slist_t *list, sys_snode_t *node) { sys_slist_prepend(list, node); }
void sys_slist_append__extern(sys_slist_t *list, sys_snode_t *node) { sys_slist_append(list, node); }
void sys_slist_append_list__extern(sys_slist_t *list, void *head, void *tail) { sys_slist_append_list(list, head, tail); }
void sys_slist_merge_slist__extern(sys_slist_t *list, sys_slist_t *list_to_append) { sys_slist_merge_slist(list, list_to_append); }
void sys_slist_insert__extern(sys_slist_t *list, sys_snode_t *prev, sys_snode_t *node) { sys_slist_insert(list, prev, node); }
sys_snode_t * sys_slist_get_not_empty__extern(sys_slist_t *list) { return sys_slist_get_not_empty(list); }
sys_snode_t * sys_slist_get__extern(sys_slist_t *list) { return sys_slist_get(list); }
void sys_slist_remove__extern(sys_slist_t *list, sys_snode_t *prev_node, sys_snode_t *node) { sys_slist_remove(list, prev_node, node); }
bool sys_slist_find_and_remove__extern(sys_slist_t *list, sys_snode_t *node) { return sys_slist_find_and_remove(list, node); }
size_t sys_slist_len__extern(sys_slist_t *list) { return sys_slist_len(list); }
void sys_sflist_init__extern(sys_sflist_t *list) { sys_sflist_init(list); }
sys_sfnode_t * z_sfnode_next_peek__extern(sys_sfnode_t *node) { return z_sfnode_next_peek(node); }
uint8_t sys_sfnode_flags_get__extern(sys_sfnode_t *node) { return sys_sfnode_flags_get(node); }
void z_sfnode_next_set__extern(sys_sfnode_t *parent, sys_sfnode_t *child) { z_sfnode_next_set(parent, child); }
void z_sflist_head_set__extern(sys_sflist_t *list, sys_sfnode_t *node) { z_sflist_head_set(list, node); }
void z_sflist_tail_set__extern(sys_sflist_t *list, sys_sfnode_t *node) { z_sflist_tail_set(list, node); }
sys_sfnode_t * sys_sflist_peek_head__extern(sys_sflist_t *list) { return sys_sflist_peek_head(list); }
sys_sfnode_t * sys_sflist_peek_tail__extern(sys_sflist_t *list) { return sys_sflist_peek_tail(list); }
void sys_sfnode_init__extern(sys_sfnode_t *node, uint8_t flags) { sys_sfnode_init(node, flags); }
void sys_sfnode_flags_set__extern(sys_sfnode_t *node, uint8_t flags) { sys_sfnode_flags_set(node, flags); }
bool sys_sflist_is_empty__extern(sys_sflist_t *list) { return sys_sflist_is_empty(list); }
sys_sfnode_t * sys_sflist_peek_next_no_check__extern(sys_sfnode_t *node) { return sys_sflist_peek_next_no_check(node); }
sys_sfnode_t * sys_sflist_peek_next__extern(sys_sfnode_t *node) { return sys_sflist_peek_next(node); }
void sys_sflist_prepend__extern(sys_sflist_t *list, sys_sfnode_t *node) { sys_sflist_prepend(list, node); }
void sys_sflist_append__extern(sys_sflist_t *list, sys_sfnode_t *node) { sys_sflist_append(list, node); }
void sys_sflist_append_list__extern(sys_sflist_t *list, void *head, void *tail) { sys_sflist_append_list(list, head, tail); }
void sys_sflist_merge_sflist__extern(sys_sflist_t *list, sys_sflist_t *list_to_append) { sys_sflist_merge_sflist(list, list_to_append); }
void sys_sflist_insert__extern(sys_sflist_t *list, sys_sfnode_t *prev, sys_sfnode_t *node) { sys_sflist_insert(list, prev, node); }
sys_sfnode_t * sys_sflist_get_not_empty__extern(sys_sflist_t *list) { return sys_sflist_get_not_empty(list); }
sys_sfnode_t * sys_sflist_get__extern(sys_sflist_t *list) { return sys_sflist_get(list); }
void sys_sflist_remove__extern(sys_sflist_t *list, sys_sfnode_t *prev_node, sys_sfnode_t *node) { sys_sflist_remove(list, prev_node, node); }
bool sys_sflist_find_and_remove__extern(sys_sflist_t *list, sys_sfnode_t *node) { return sys_sflist_find_and_remove(list, node); }
size_t sys_sflist_len__extern(sys_sflist_t *list) { return sys_sflist_len(list); }
bool z_syscall_trap__extern(void) { return z_syscall_trap(); }
bool k_is_user_context__extern(void) { return k_is_user_context(); }
int __sputc_r__extern(struct _reent *_ptr, int _c, FILE *_p) { return __sputc_r(_ptr, _c, _p); }
int _getchar_unlocked__extern(void) { return _getchar_unlocked(); }
int _putchar_unlocked__extern(int _c) { return _putchar_unlocked(_c); }
uint32_t arch_k_cycle_get_32__extern(void) { return arch_k_cycle_get_32(); }
uint64_t arch_k_cycle_get_64__extern(void) { return arch_k_cycle_get_64(); }
unsigned int arch_irq_lock__extern(void) { return arch_irq_lock(); }
void arch_irq_unlock__extern(unsigned int key) { arch_irq_unlock(key); }
bool arch_irq_unlocked__extern(unsigned int key) { return arch_irq_unlocked(key); }
unsigned int arch_num_cpus__extern(void) { return arch_num_cpus(); }
bool arch_mem_coherent__extern(void *ptr) { return arch_mem_coherent(ptr); }
void arch_cohere_stacks__extern(struct k_thread *old_thread, void *old_switch_handle, struct k_thread *new_thread) { arch_cohere_stacks(old_thread, old_switch_handle, new_thread); }
uint32_t read_mpuir__extern(void) { return read_mpuir(); }
void write_mpuir__extern(uint32_t val) { write_mpuir(val); }
uint32_t read_mpidr__extern(void) { return read_mpidr(); }
void write_mpidr__extern(uint32_t val) { write_mpidr(val); }
uint32_t read_sctlr__extern(void) { return read_sctlr(); }
void write_sctlr__extern(uint32_t val) { write_sctlr(val); }
uint32_t read_prselr__extern(void) { return read_prselr(); }
void write_prselr__extern(uint32_t val) { write_prselr(val); }
uint32_t read_prbar__extern(void) { return read_prbar(); }
void write_prbar__extern(uint32_t val) { write_prbar(val); }
uint32_t read_prlar__extern(void) { return read_prlar(); }
void write_prlar__extern(uint32_t val) { write_prlar(val); }
uint32_t read_mair0__extern(void) { return read_mair0(); }
void write_mair0__extern(uint32_t val) { write_mair0(val); }
uint32_t read_vbar__extern(void) { return read_vbar(); }
void write_vbar__extern(uint32_t val) { write_vbar(val); }
uint32_t read_cntv_ctl__extern(void) { return read_cntv_ctl(); }
void write_cntv_ctl__extern(uint32_t val) { write_cntv_ctl(val); }
uint32_t read_ctr__extern(void) { return read_ctr(); }
void write_ctr__extern(uint32_t val) { write_ctr(val); }
uint32_t read_tpidruro__extern(void) { return read_tpidruro(); }
void write_tpidruro__extern(uint32_t val) { write_tpidruro(val); }
uint64_t read_ICC_SGI1R__extern(void) { return read_ICC_SGI1R(); }
void write_ICC_SGI1R__extern(uint64_t val) { write_ICC_SGI1R(val); }
uint64_t read_cntvct__extern(void) { return read_cntvct(); }
void write_cntvct__extern(uint64_t val) { write_cntvct(val); }
uint64_t read_cntv_cval__extern(void) { return read_cntv_cval(); }
void write_cntv_cval__extern(uint64_t val) { write_cntv_cval(val); }
uint32_t read_ICC_PMR_EL1__extern(void) { return read_ICC_PMR_EL1(); }
void write_ICC_PMR_EL1__extern(uint32_t val) { write_ICC_PMR_EL1(val); }
uint32_t read_ICC_IAR1_EL1__extern(void) { return read_ICC_IAR1_EL1(); }
void write_ICC_IAR1_EL1__extern(uint32_t val) { write_ICC_IAR1_EL1(val); }
uint32_t read_ICC_EOIR1_EL1__extern(void) { return read_ICC_EOIR1_EL1(); }
void write_ICC_EOIR1_EL1__extern(uint32_t val) { write_ICC_EOIR1_EL1(val); }
uint32_t read_ICC_SRE_EL1__extern(void) { return read_ICC_SRE_EL1(); }
void write_ICC_SRE_EL1__extern(uint32_t val) { write_ICC_SRE_EL1(val); }
uint32_t read_ICC_IGRPEN1_EL1__extern(void) { return read_ICC_IGRPEN1_EL1(); }
void write_ICC_IGRPEN1_EL1__extern(uint32_t val) { write_ICC_IGRPEN1_EL1(val); }
_cpu_t * arch_curr_cpu__extern(void) { return arch_curr_cpu(); }
uint32_t arch_proc_id__extern(void) { return arch_proc_id(); }
unsigned int irq_get_level__extern(unsigned int irq) { return irq_get_level(irq); }
unsigned int irq_from_level_2__extern(unsigned int irq) { return irq_from_level_2(irq); }
unsigned int irq_to_level_2__extern(unsigned int irq) { return irq_to_level_2(irq); }
unsigned int irq_parent_level_2__extern(unsigned int irq) { return irq_parent_level_2(irq); }
unsigned int irq_from_level_3__extern(unsigned int irq) { return irq_from_level_3(irq); }
unsigned int irq_to_level_3__extern(unsigned int irq) { return irq_to_level_3(irq); }
unsigned int irq_parent_level_3__extern(unsigned int irq) { return irq_parent_level_3(irq); }
uintptr_t z_mem_phys_addr__extern(void *virt) { return z_mem_phys_addr(virt); }
void * z_mem_virt_addr__extern(uintptr_t phys) { return z_mem_virt_addr(phys); }
void k_mem_paging_stats_get__extern(struct k_mem_paging_stats_t *stats) { k_mem_paging_stats_get(stats); }
void k_mem_paging_thread_stats_get__extern(struct k_thread *thread, struct k_mem_paging_stats_t *stats) { k_mem_paging_thread_stats_get(thread, stats); }
void k_mem_paging_histogram_eviction_get__extern(struct k_mem_paging_histogram_t *hist) { k_mem_paging_histogram_eviction_get(hist); }
void k_mem_paging_histogram_backing_store_page_in_get__extern(struct k_mem_paging_histogram_t *hist) { k_mem_paging_histogram_backing_store_page_in_get(hist); }
void k_mem_paging_histogram_backing_store_page_out_get__extern(struct k_mem_paging_histogram_t *hist) { k_mem_paging_histogram_backing_store_page_out_get(hist); }
device_handle_t device_handle_get__extern(const struct device *dev) { return device_handle_get(dev); }
const struct device * device_from_handle__extern(device_handle_t dev_handle) { return device_from_handle(dev_handle); }
const struct device * device_get_binding__extern(const char *name) { return device_get_binding(name); }
bool device_is_ready__extern(const struct device *dev) { return device_is_ready(dev); }
bool z_impl_device_is_ready__extern(const struct device *dev) { return z_impl_device_is_ready(dev); }
void arch_isr_direct_header__extern(void) { arch_isr_direct_header(); }
void arch_isr_direct_footer__extern(int maybe_swap) { arch_isr_direct_footer(maybe_swap); }
void arch_nop__extern(void) { arch_nop(); }
unsigned int find_msb_set__extern(uint32_t op) { return find_msb_set(op); }
unsigned int find_lsb_set__extern(uint32_t op) { return find_lsb_set(op); }
void sys_set_bit__extern(mem_addr_t addr, unsigned int bit) { sys_set_bit(addr, bit); }
void sys_clear_bit__extern(mem_addr_t addr, unsigned int bit) { sys_clear_bit(addr, bit); }
int sys_test_bit__extern(mem_addr_t addr, unsigned int bit) { return sys_test_bit(addr, bit); }
void sys_set_bits__extern(mem_addr_t addr, unsigned int mask) { sys_set_bits(addr, mask); }
void sys_clear_bits__extern(mem_addr_t addr, unsigned int mask) { sys_clear_bits(addr, mask); }
void sys_bitfield_set_bit__extern(mem_addr_t addr, unsigned int bit) { sys_bitfield_set_bit(addr, bit); }
void sys_bitfield_clear_bit__extern(mem_addr_t addr, unsigned int bit) { sys_bitfield_clear_bit(addr, bit); }
int sys_bitfield_test_bit__extern(mem_addr_t addr, unsigned int bit) { return sys_bitfield_test_bit(addr, bit); }
int sys_test_and_set_bit__extern(mem_addr_t addr, unsigned int bit) { return sys_test_and_set_bit(addr, bit); }
int sys_test_and_clear_bit__extern(mem_addr_t addr, unsigned int bit) { return sys_test_and_clear_bit(addr, bit); }
int sys_bitfield_test_and_set_bit__extern(mem_addr_t addr, unsigned int bit) { return sys_bitfield_test_and_set_bit(addr, bit); }
int sys_bitfield_test_and_clear_bit__extern(mem_addr_t addr, unsigned int bit) { return sys_bitfield_test_and_clear_bit(addr, bit); }
uint8_t sys_read8__extern(mem_addr_t addr) { return sys_read8(addr); }
void sys_write8__extern(uint8_t data, mem_addr_t addr) { sys_write8(data, addr); }
uint16_t sys_read16__extern(mem_addr_t addr) { return sys_read16(addr); }
void sys_write16__extern(uint16_t data, mem_addr_t addr) { sys_write16(data, addr); }
uint32_t sys_read32__extern(mem_addr_t addr) { return sys_read32(addr); }
void sys_write32__extern(uint32_t data, mem_addr_t addr) { sys_write32(data, addr); }
uint64_t sys_read64__extern(mem_addr_t addr) { return sys_read64(addr); }
void sys_write64__extern(uint64_t data, mem_addr_t addr) { sys_write64(data, addr); }
void __ISB__extern(void) { __ISB(); }
void __DSB__extern(void) { __DSB(); }
void __DMB__extern(void) { __DMB(); }
uint32_t __REV__extern(uint32_t value) { return __REV(value); }
uint32_t __REV16__extern(uint32_t value) { return __REV16(value); }
int16_t __REVSH__extern(int16_t value) { return __REVSH(value); }
uint32_t __ROR__extern(uint32_t op1, uint32_t op2) { return __ROR(op1, op2); }
uint32_t __RBIT__extern(uint32_t value) { return __RBIT(value); }
uint8_t __CLZ__extern(uint32_t value) { return __CLZ(value); }
uint8_t __LDREXB__extern(uint8_t *addr) { return __LDREXB(addr); }
uint16_t __LDREXH__extern(uint16_t *addr) { return __LDREXH(addr); }
uint32_t __LDREXW__extern(uint32_t *addr) { return __LDREXW(addr); }
uint32_t __STREXB__extern(uint8_t value, uint8_t *addr) { return __STREXB(value, addr); }
uint32_t __STREXH__extern(uint16_t value, uint16_t *addr) { return __STREXH(value, addr); }
uint32_t __STREXW__extern(uint32_t value, uint32_t *addr) { return __STREXW(value, addr); }
void __CLREX__extern(void) { __CLREX(); }
uint32_t __RRX__extern(uint32_t value) { return __RRX(value); }
uint8_t __LDRBT__extern(uint8_t *ptr) { return __LDRBT(ptr); }
uint16_t __LDRHT__extern(uint16_t *ptr) { return __LDRHT(ptr); }
uint32_t __LDRT__extern(uint32_t *ptr) { return __LDRT(ptr); }
void __STRBT__extern(uint8_t value, uint8_t *ptr) { __STRBT(value, ptr); }
void __STRHT__extern(uint16_t value, uint16_t *ptr) { __STRHT(value, ptr); }
void __STRT__extern(uint32_t value, uint32_t *ptr) { __STRT(value, ptr); }
void __enable_irq__extern(void) { __enable_irq(); }
void __disable_irq__extern(void) { __disable_irq(); }
uint32_t __get_CONTROL__extern(void) { return __get_CONTROL(); }
void __set_CONTROL__extern(uint32_t control) { __set_CONTROL(control); }
uint32_t __get_IPSR__extern(void) { return __get_IPSR(); }
uint32_t __get_APSR__extern(void) { return __get_APSR(); }
uint32_t __get_xPSR__extern(void) { return __get_xPSR(); }
uint32_t __get_PSP__extern(void) { return __get_PSP(); }
void __set_PSP__extern(uint32_t topOfProcStack) { __set_PSP(topOfProcStack); }
uint32_t __get_MSP__extern(void) { return __get_MSP(); }
void __set_MSP__extern(uint32_t topOfMainStack) { __set_MSP(topOfMainStack); }
uint32_t __get_PRIMASK__extern(void) { return __get_PRIMASK(); }
void __set_PRIMASK__extern(uint32_t priMask) { __set_PRIMASK(priMask); }
void __enable_fault_irq__extern(void) { __enable_fault_irq(); }
void __disable_fault_irq__extern(void) { __disable_fault_irq(); }
uint32_t __get_BASEPRI__extern(void) { return __get_BASEPRI(); }
void __set_BASEPRI__extern(uint32_t basePri) { __set_BASEPRI(basePri); }
void __set_BASEPRI_MAX__extern(uint32_t basePri) { __set_BASEPRI_MAX(basePri); }
uint32_t __get_FAULTMASK__extern(void) { return __get_FAULTMASK(); }
void __set_FAULTMASK__extern(uint32_t faultMask) { __set_FAULTMASK(faultMask); }
uint32_t __get_FPSCR__extern(void) { return __get_FPSCR(); }
void __set_FPSCR__extern(uint32_t fpscr) { __set_FPSCR(fpscr); }
uint32_t __SADD8__extern(uint32_t op1, uint32_t op2) { return __SADD8(op1, op2); }
uint32_t __QADD8__extern(uint32_t op1, uint32_t op2) { return __QADD8(op1, op2); }
uint32_t __SHADD8__extern(uint32_t op1, uint32_t op2) { return __SHADD8(op1, op2); }
uint32_t __UADD8__extern(uint32_t op1, uint32_t op2) { return __UADD8(op1, op2); }
uint32_t __UQADD8__extern(uint32_t op1, uint32_t op2) { return __UQADD8(op1, op2); }
uint32_t __UHADD8__extern(uint32_t op1, uint32_t op2) { return __UHADD8(op1, op2); }
uint32_t __SSUB8__extern(uint32_t op1, uint32_t op2) { return __SSUB8(op1, op2); }
uint32_t __QSUB8__extern(uint32_t op1, uint32_t op2) { return __QSUB8(op1, op2); }
uint32_t __SHSUB8__extern(uint32_t op1, uint32_t op2) { return __SHSUB8(op1, op2); }
uint32_t __USUB8__extern(uint32_t op1, uint32_t op2) { return __USUB8(op1, op2); }
uint32_t __UQSUB8__extern(uint32_t op1, uint32_t op2) { return __UQSUB8(op1, op2); }
uint32_t __UHSUB8__extern(uint32_t op1, uint32_t op2) { return __UHSUB8(op1, op2); }
uint32_t __SADD16__extern(uint32_t op1, uint32_t op2) { return __SADD16(op1, op2); }
uint32_t __QADD16__extern(uint32_t op1, uint32_t op2) { return __QADD16(op1, op2); }
uint32_t __SHADD16__extern(uint32_t op1, uint32_t op2) { return __SHADD16(op1, op2); }
uint32_t __UADD16__extern(uint32_t op1, uint32_t op2) { return __UADD16(op1, op2); }
uint32_t __UQADD16__extern(uint32_t op1, uint32_t op2) { return __UQADD16(op1, op2); }
uint32_t __UHADD16__extern(uint32_t op1, uint32_t op2) { return __UHADD16(op1, op2); }
uint32_t __SSUB16__extern(uint32_t op1, uint32_t op2) { return __SSUB16(op1, op2); }
uint32_t __QSUB16__extern(uint32_t op1, uint32_t op2) { return __QSUB16(op1, op2); }
uint32_t __SHSUB16__extern(uint32_t op1, uint32_t op2) { return __SHSUB16(op1, op2); }
uint32_t __USUB16__extern(uint32_t op1, uint32_t op2) { return __USUB16(op1, op2); }
uint32_t __UQSUB16__extern(uint32_t op1, uint32_t op2) { return __UQSUB16(op1, op2); }
uint32_t __UHSUB16__extern(uint32_t op1, uint32_t op2) { return __UHSUB16(op1, op2); }
uint32_t __SASX__extern(uint32_t op1, uint32_t op2) { return __SASX(op1, op2); }
uint32_t __QASX__extern(uint32_t op1, uint32_t op2) { return __QASX(op1, op2); }
uint32_t __SHASX__extern(uint32_t op1, uint32_t op2) { return __SHASX(op1, op2); }
uint32_t __UASX__extern(uint32_t op1, uint32_t op2) { return __UASX(op1, op2); }
uint32_t __UQASX__extern(uint32_t op1, uint32_t op2) { return __UQASX(op1, op2); }
uint32_t __UHASX__extern(uint32_t op1, uint32_t op2) { return __UHASX(op1, op2); }
uint32_t __SSAX__extern(uint32_t op1, uint32_t op2) { return __SSAX(op1, op2); }
uint32_t __QSAX__extern(uint32_t op1, uint32_t op2) { return __QSAX(op1, op2); }
uint32_t __SHSAX__extern(uint32_t op1, uint32_t op2) { return __SHSAX(op1, op2); }
uint32_t __USAX__extern(uint32_t op1, uint32_t op2) { return __USAX(op1, op2); }
uint32_t __UQSAX__extern(uint32_t op1, uint32_t op2) { return __UQSAX(op1, op2); }
uint32_t __UHSAX__extern(uint32_t op1, uint32_t op2) { return __UHSAX(op1, op2); }
uint32_t __USAD8__extern(uint32_t op1, uint32_t op2) { return __USAD8(op1, op2); }
uint32_t __USADA8__extern(uint32_t op1, uint32_t op2, uint32_t op3) { return __USADA8(op1, op2, op3); }
uint32_t __UXTB16__extern(uint32_t op1) { return __UXTB16(op1); }
uint32_t __UXTAB16__extern(uint32_t op1, uint32_t op2) { return __UXTAB16(op1, op2); }
uint32_t __SXTB16__extern(uint32_t op1) { return __SXTB16(op1); }
uint32_t __SXTB16_RORn__extern(uint32_t op1, uint32_t rotate) { return __SXTB16_RORn(op1, rotate); }
uint32_t __SXTAB16__extern(uint32_t op1, uint32_t op2) { return __SXTAB16(op1, op2); }
uint32_t __SXTAB16_RORn__extern(uint32_t op1, uint32_t op2, uint32_t rotate) { return __SXTAB16_RORn(op1, op2, rotate); }
uint32_t __SMUAD__extern(uint32_t op1, uint32_t op2) { return __SMUAD(op1, op2); }
uint32_t __SMUADX__extern(uint32_t op1, uint32_t op2) { return __SMUADX(op1, op2); }
uint32_t __SMLAD__extern(uint32_t op1, uint32_t op2, uint32_t op3) { return __SMLAD(op1, op2, op3); }
uint32_t __SMLADX__extern(uint32_t op1, uint32_t op2, uint32_t op3) { return __SMLADX(op1, op2, op3); }
uint64_t __SMLALD__extern(uint32_t op1, uint32_t op2, uint64_t acc) { return __SMLALD(op1, op2, acc); }
uint64_t __SMLALDX__extern(uint32_t op1, uint32_t op2, uint64_t acc) { return __SMLALDX(op1, op2, acc); }
uint32_t __SMUSD__extern(uint32_t op1, uint32_t op2) { return __SMUSD(op1, op2); }
uint32_t __SMUSDX__extern(uint32_t op1, uint32_t op2) { return __SMUSDX(op1, op2); }
uint32_t __SMLSD__extern(uint32_t op1, uint32_t op2, uint32_t op3) { return __SMLSD(op1, op2, op3); }
uint32_t __SMLSDX__extern(uint32_t op1, uint32_t op2, uint32_t op3) { return __SMLSDX(op1, op2, op3); }
uint64_t __SMLSLD__extern(uint32_t op1, uint32_t op2, uint64_t acc) { return __SMLSLD(op1, op2, acc); }
uint64_t __SMLSLDX__extern(uint32_t op1, uint32_t op2, uint64_t acc) { return __SMLSLDX(op1, op2, acc); }
uint32_t __SEL__extern(uint32_t op1, uint32_t op2) { return __SEL(op1, op2); }
int32_t __QADD__extern(int32_t op1, int32_t op2) { return __QADD(op1, op2); }
int32_t __QSUB__extern(int32_t op1, int32_t op2) { return __QSUB(op1, op2); }
int32_t __SMMLA__extern(int32_t op1, int32_t op2, int32_t op3) { return __SMMLA(op1, op2, op3); }
void __NVIC_SetPriorityGrouping__extern(uint32_t PriorityGroup) { __NVIC_SetPriorityGrouping(PriorityGroup); }
uint32_t __NVIC_GetPriorityGrouping__extern(void) { return __NVIC_GetPriorityGrouping(); }
void __NVIC_EnableIRQ__extern(IRQn_Type IRQn) { __NVIC_EnableIRQ(IRQn); }
uint32_t __NVIC_GetEnableIRQ__extern(IRQn_Type IRQn) { return __NVIC_GetEnableIRQ(IRQn); }
void __NVIC_DisableIRQ__extern(IRQn_Type IRQn) { __NVIC_DisableIRQ(IRQn); }
uint32_t __NVIC_GetPendingIRQ__extern(IRQn_Type IRQn) { return __NVIC_GetPendingIRQ(IRQn); }
void __NVIC_SetPendingIRQ__extern(IRQn_Type IRQn) { __NVIC_SetPendingIRQ(IRQn); }
void __NVIC_ClearPendingIRQ__extern(IRQn_Type IRQn) { __NVIC_ClearPendingIRQ(IRQn); }
uint32_t __NVIC_GetActive__extern(IRQn_Type IRQn) { return __NVIC_GetActive(IRQn); }
void __NVIC_SetPriority__extern(IRQn_Type IRQn, uint32_t priority) { __NVIC_SetPriority(IRQn, priority); }
uint32_t __NVIC_GetPriority__extern(IRQn_Type IRQn) { return __NVIC_GetPriority(IRQn); }
uint32_t NVIC_EncodePriority__extern(uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority) { return NVIC_EncodePriority(PriorityGroup, PreemptPriority, SubPriority); }
void NVIC_DecodePriority__extern(uint32_t Priority, uint32_t PriorityGroup, const uint32_t *const pPreemptPriority, const uint32_t *const pSubPriority) { NVIC_DecodePriority(Priority, PriorityGroup, pPreemptPriority, pSubPriority); }
void __NVIC_SetVector__extern(IRQn_Type IRQn, uint32_t vector) { __NVIC_SetVector(IRQn, vector); }
uint32_t __NVIC_GetVector__extern(IRQn_Type IRQn) { return __NVIC_GetVector(IRQn); }
void __NVIC_SystemReset__extern(void) { __NVIC_SystemReset(); }
void ARM_MPU_Enable__extern(uint32_t MPU_Control) { ARM_MPU_Enable(MPU_Control); }
void ARM_MPU_Disable__extern(void) { ARM_MPU_Disable(); }
void ARM_MPU_ClrRegion__extern(uint32_t rnr) { ARM_MPU_ClrRegion(rnr); }
void ARM_MPU_SetRegion__extern(uint32_t rbar, uint32_t rasr) { ARM_MPU_SetRegion(rbar, rasr); }
void ARM_MPU_SetRegionEx__extern(uint32_t rnr, uint32_t rbar, uint32_t rasr) { ARM_MPU_SetRegionEx(rnr, rbar, rasr); }
void ARM_MPU_OrderedMemcpy__extern(uint32_t *dst, const uint32_t *src, uint32_t len) { ARM_MPU_OrderedMemcpy(dst, src, len); }
void ARM_MPU_Load__extern(const ARM_MPU_Region_t *table, uint32_t cnt) { ARM_MPU_Load(table, cnt); }
uint32_t SCB_GetFPUType__extern(void) { return SCB_GetFPUType(); }
uint32_t SysTick_Config__extern(uint32_t ticks) { return SysTick_Config(ticks); }
uint32_t ITM_SendChar__extern(uint32_t ch) { return ITM_SendChar(ch); }
int32_t ITM_ReceiveChar__extern(void) { return ITM_ReceiveChar(); }
int32_t ITM_CheckChar__extern(void) { return ITM_CheckChar(); }
unsigned int gcc_current_sp__extern(void) { return gcc_current_sp(); }
bool nrfx_is_in_ram__extern(const void *p_object) { return nrfx_is_in_ram(p_object); }
bool nrfx_is_word_aligned__extern(const void *p_object) { return nrfx_is_word_aligned(p_object); }
IRQn_Type nrfx_get_irq_number__extern(const void *p_reg) { return nrfx_get_irq_number(p_reg); }
uint32_t nrfx_bitpos_to_event__extern(uint32_t bit) { return nrfx_bitpos_to_event(bit); }
uint32_t nrfx_event_to_bitpos__extern(uint32_t event) { return nrfx_event_to_bitpos(event); }
int irq_connect_dynamic__extern(unsigned int irq, unsigned int priority, void (*routine) (const void *parameter), const void *parameter, uint32_t flags) { return irq_connect_dynamic(irq, priority, routine, parameter, flags); }
int irq_disconnect_dynamic__extern(unsigned int irq, unsigned int priority, void (*routine) (const void *parameter), const void *parameter, uint32_t flags) { return irq_disconnect_dynamic(irq, priority, routine, parameter, flags); }
bool nrf_dma_accessible_check__extern(const void *p_reg, const void *p_object) { return nrf_dma_accessible_check(p_reg, p_object); }
void nrf_barrier_w__extern(void) { nrf_barrier_w(); }
void nrf_barrier_r__extern(void) { nrf_barrier_r(); }
void nrf_barrier_rw__extern(void) { nrf_barrier_rw(); }
bool nrf_event_check__extern(const void *p_reg, uint32_t event) { return nrf_event_check(p_reg, event); }
uint32_t nrf_task_event_address_get__extern(const void *p_reg, uint32_t task_event) { return nrf_task_event_address_get(p_reg, task_event); }
void nrf_event_readback__extern(void *p_event_reg) { nrf_event_readback(p_event_reg); }
uint64_t sys_clock_timeout_end_calc__extern(k_timeout_t timeout) { return sys_clock_timeout_end_calc(timeout); }
int sys_timepoint_cmp__extern(k_timepoint_t a, k_timepoint_t b) { return sys_timepoint_cmp(a, b); }
bool sys_timepoint_expired__extern(k_timepoint_t timepoint) { return sys_timepoint_expired(timepoint); }
void z_spinlock_validate_pre__extern(struct k_spinlock *l) { z_spinlock_validate_pre(l); }
void z_spinlock_validate_post__extern(struct k_spinlock *l) { z_spinlock_validate_post(l); }
k_spinlock_key_t k_spin_lock__extern(struct k_spinlock *l) { return k_spin_lock(l); }
int k_spin_trylock__extern(struct k_spinlock *l, k_spinlock_key_t *k) { return k_spin_trylock(l, k); }
void k_spin_unlock__extern(struct k_spinlock *l, k_spinlock_key_t key) { k_spin_unlock(l, key); }
void k_spin_release__extern(struct k_spinlock *l) { k_spin_release(l); }
char * z_stack_ptr_align__extern(char *ptr) { return z_stack_ptr_align(ptr); }
char * Z_KERNEL_STACK_BUFFER__extern(k_thread_stack_t *sym) { return Z_KERNEL_STACK_BUFFER(sym); }
void k_object_init__extern(const void *obj) { k_object_init(obj); }
struct k_object * k_object_create_dynamic_aligned__extern(size_t align, size_t size) { return k_object_create_dynamic_aligned(align, size); }
struct k_object * k_object_create_dynamic__extern(size_t size) { return k_object_create_dynamic(size); }
void z_impl_k_object_access_grant__extern(const void *object, struct k_thread *thread) { z_impl_k_object_access_grant(object, thread); }
void k_object_access_revoke__extern(const void *object, struct k_thread *thread) { k_object_access_revoke(object, thread); }
void z_impl_k_object_release__extern(const void *object) { z_impl_k_object_release(object); }
void k_object_access_all_grant__extern(const void *object) { k_object_access_all_grant(object); }
bool k_object_is_valid__extern(const void *obj, enum k_objects otype) { return k_object_is_valid(obj, otype); }
void * z_impl_k_object_alloc__extern(enum k_objects otype) { return z_impl_k_object_alloc(otype); }
void * z_impl_k_object_alloc_size__extern(enum k_objects otype, size_t size) { return z_impl_k_object_alloc_size(otype, size); }
void k_object_free__extern(void *obj) { k_object_free(obj); }
void k_object_access_grant__extern(const void *object, struct k_thread *thread) { k_object_access_grant(object, thread); }
void k_object_release__extern(const void *object) { k_object_release(object); }
void * k_object_alloc__extern(enum k_objects otype) { return k_object_alloc(otype); }
void * k_object_alloc_size__extern(enum k_objects otype, size_t size) { return k_object_alloc_size(otype, size); }
k_thread_stack_t * k_thread_stack_alloc__extern(size_t size, int flags) { return k_thread_stack_alloc(size, flags); }
int k_thread_stack_free__extern(k_thread_stack_t *stack) { return k_thread_stack_free(stack); }
k_tid_t k_thread_create__extern(struct k_thread *new_thread, k_thread_stack_t *stack, size_t stack_size, k_thread_entry_t entry, void *p1, void *p2, void *p3, int prio, uint32_t options, k_timeout_t delay) { return k_thread_create(new_thread, stack, stack_size, entry, p1, p2, p3, prio, options, delay); }
void k_thread_heap_assign__extern(struct k_thread *thread, struct k_heap *heap) { k_thread_heap_assign(thread, heap); }
int k_thread_join__extern(struct k_thread *thread, k_timeout_t timeout) { return k_thread_join(thread, timeout); }
int32_t k_sleep__extern(k_timeout_t timeout) { return k_sleep(timeout); }
int32_t k_msleep__extern(int32_t ms) { return k_msleep(ms); }
int32_t k_usleep__extern(int32_t us) { return k_usleep(us); }
void k_busy_wait__extern(uint32_t usec_to_wait) { k_busy_wait(usec_to_wait); }
void k_yield__extern(void) { k_yield(); }
void k_wakeup__extern(k_tid_t thread) { k_wakeup(thread); }
k_tid_t k_sched_current_thread_query__extern(void) { return k_sched_current_thread_query(); }
k_tid_t k_current_get__extern(void) { return k_current_get(); }
void k_thread_abort__extern(k_tid_t thread) { k_thread_abort(thread); }
void k_thread_start__extern(k_tid_t thread) { k_thread_start(thread); }
k_ticks_t k_thread_timeout_expires_ticks__extern(const struct k_thread *t) { return k_thread_timeout_expires_ticks(t); }
k_ticks_t z_impl_k_thread_timeout_expires_ticks__extern(const struct k_thread *t) { return z_impl_k_thread_timeout_expires_ticks(t); }
k_ticks_t k_thread_timeout_remaining_ticks__extern(const struct k_thread *t) { return k_thread_timeout_remaining_ticks(t); }
k_ticks_t z_impl_k_thread_timeout_remaining_ticks__extern(const struct k_thread *t) { return z_impl_k_thread_timeout_remaining_ticks(t); }
int k_thread_priority_get__extern(k_tid_t thread) { return k_thread_priority_get(thread); }
void k_thread_priority_set__extern(k_tid_t thread, int prio) { k_thread_priority_set(thread, prio); }
void k_thread_suspend__extern(k_tid_t thread) { k_thread_suspend(thread); }
void k_thread_resume__extern(k_tid_t thread) { k_thread_resume(thread); }
int k_is_preempt_thread__extern(void) { return k_is_preempt_thread(); }
bool k_is_pre_kernel__extern(void) { return k_is_pre_kernel(); }
void k_thread_custom_data_set__extern(void *value) { k_thread_custom_data_set(value); }
void * k_thread_custom_data_get__extern(void) { return k_thread_custom_data_get(); }
int k_thread_name_set__extern(k_tid_t thread, const char *str) { return k_thread_name_set(thread, str); }
int k_thread_name_copy__extern(k_tid_t thread, char *buf, size_t size) { return k_thread_name_copy(thread, buf, size); }
void k_timer_start__extern(struct k_timer *timer, k_timeout_t duration, k_timeout_t period) { k_timer_start(timer, duration, period); }
void k_timer_stop__extern(struct k_timer *timer) { k_timer_stop(timer); }
uint32_t k_timer_status_get__extern(struct k_timer *timer) { return k_timer_status_get(timer); }
uint32_t k_timer_status_sync__extern(struct k_timer *timer) { return k_timer_status_sync(timer); }
k_ticks_t k_timer_expires_ticks__extern(const struct k_timer *timer) { return k_timer_expires_ticks(timer); }
k_ticks_t z_impl_k_timer_expires_ticks__extern(const struct k_timer *timer) { return z_impl_k_timer_expires_ticks(timer); }
k_ticks_t k_timer_remaining_ticks__extern(const struct k_timer *timer) { return k_timer_remaining_ticks(timer); }
k_ticks_t z_impl_k_timer_remaining_ticks__extern(const struct k_timer *timer) { return z_impl_k_timer_remaining_ticks(timer); }
uint32_t k_timer_remaining_get__extern(struct k_timer *timer) { return k_timer_remaining_get(timer); }
void k_timer_user_data_set__extern(struct k_timer *timer, void *user_data) { k_timer_user_data_set(timer, user_data); }
void z_impl_k_timer_user_data_set__extern(struct k_timer *timer, void *user_data) { z_impl_k_timer_user_data_set(timer, user_data); }
void * k_timer_user_data_get__extern(const struct k_timer *timer) { return k_timer_user_data_get(timer); }
void * z_impl_k_timer_user_data_get__extern(const struct k_timer *timer) { return z_impl_k_timer_user_data_get(timer); }
int64_t k_uptime_ticks__extern(void) { return k_uptime_ticks(); }
int64_t k_uptime_get__extern(void) { return k_uptime_get(); }
uint32_t k_uptime_get_32__extern(void) { return k_uptime_get_32(); }
int64_t k_uptime_delta__extern(int64_t *reftime) { return k_uptime_delta(reftime); }
uint32_t k_cycle_get_32__extern(void) { return k_cycle_get_32(); }
uint64_t k_cycle_get_64__extern(void) { return k_cycle_get_64(); }
void k_queue_init__extern(struct k_queue *queue) { k_queue_init(queue); }
void k_queue_cancel_wait__extern(struct k_queue *queue) { k_queue_cancel_wait(queue); }
int32_t k_queue_alloc_append__extern(struct k_queue *queue, void *data) { return k_queue_alloc_append(queue, data); }
int32_t k_queue_alloc_prepend__extern(struct k_queue *queue, void *data) { return k_queue_alloc_prepend(queue, data); }
void * k_queue_get__extern(struct k_queue *queue, k_timeout_t timeout) { return k_queue_get(queue, timeout); }
int k_queue_is_empty__extern(struct k_queue *queue) { return k_queue_is_empty(queue); }
int z_impl_k_queue_is_empty__extern(struct k_queue *queue) { return z_impl_k_queue_is_empty(queue); }
void * k_queue_peek_head__extern(struct k_queue *queue) { return k_queue_peek_head(queue); }
void * k_queue_peek_tail__extern(struct k_queue *queue) { return k_queue_peek_tail(queue); }
void k_event_init__extern(struct k_event *event) { k_event_init(event); }
uint32_t k_event_post__extern(struct k_event *event, uint32_t events) { return k_event_post(event, events); }
uint32_t k_event_set__extern(struct k_event *event, uint32_t events) { return k_event_set(event, events); }
uint32_t k_event_set_masked__extern(struct k_event *event, uint32_t events, uint32_t events_mask) { return k_event_set_masked(event, events, events_mask); }
uint32_t k_event_clear__extern(struct k_event *event, uint32_t events) { return k_event_clear(event, events); }
uint32_t k_event_wait__extern(struct k_event *event, uint32_t events, bool reset, k_timeout_t timeout) { return k_event_wait(event, events, reset, timeout); }
uint32_t k_event_wait_all__extern(struct k_event *event, uint32_t events, bool reset, k_timeout_t timeout) { return k_event_wait_all(event, events, reset, timeout); }
uint32_t k_event_test__extern(struct k_event *event, uint32_t events_mask) { return k_event_test(event, events_mask); }
int32_t k_stack_alloc_init__extern(struct k_stack *stack, uint32_t num_entries) { return k_stack_alloc_init(stack, num_entries); }
int k_stack_push__extern(struct k_stack *stack, stack_data_t data) { return k_stack_push(stack, data); }
int k_stack_pop__extern(struct k_stack *stack, stack_data_t *data, k_timeout_t timeout) { return k_stack_pop(stack, data, timeout); }
int k_mutex_init__extern(struct k_mutex *mutex) { return k_mutex_init(mutex); }
int k_mutex_lock__extern(struct k_mutex *mutex, k_timeout_t timeout) { return k_mutex_lock(mutex, timeout); }
int k_mutex_unlock__extern(struct k_mutex *mutex) { return k_mutex_unlock(mutex); }
int k_condvar_init__extern(struct k_condvar *condvar) { return k_condvar_init(condvar); }
int k_condvar_signal__extern(struct k_condvar *condvar) { return k_condvar_signal(condvar); }
int k_condvar_broadcast__extern(struct k_condvar *condvar) { return k_condvar_broadcast(condvar); }
int k_condvar_wait__extern(struct k_condvar *condvar, struct k_mutex *mutex, k_timeout_t timeout) { return k_condvar_wait(condvar, mutex, timeout); }
int k_sem_init__extern(struct k_sem *sem, unsigned int initial_count, unsigned int limit) { return k_sem_init(sem, initial_count, limit); }
int k_sem_take__extern(struct k_sem *sem, k_timeout_t timeout) { return k_sem_take(sem, timeout); }
void k_sem_give__extern(struct k_sem *sem) { k_sem_give(sem); }
void k_sem_reset__extern(struct k_sem *sem) { k_sem_reset(sem); }
unsigned int k_sem_count_get__extern(struct k_sem *sem) { return k_sem_count_get(sem); }
unsigned int z_impl_k_sem_count_get__extern(struct k_sem *sem) { return z_impl_k_sem_count_get(sem); }
bool k_work_is_pending__extern(const struct k_work *work) { return k_work_is_pending(work); }
k_tid_t k_work_queue_thread_get__extern(struct k_work_q *queue) { return k_work_queue_thread_get(queue); }
struct k_work_delayable * k_work_delayable_from_work__extern(struct k_work *work) { return k_work_delayable_from_work(work); }
bool k_work_delayable_is_pending__extern(const struct k_work_delayable *dwork) { return k_work_delayable_is_pending(dwork); }
k_ticks_t k_work_delayable_expires_get__extern(const struct k_work_delayable *dwork) { return k_work_delayable_expires_get(dwork); }
k_ticks_t k_work_delayable_remaining_get__extern(const struct k_work_delayable *dwork) { return k_work_delayable_remaining_get(dwork); }
void k_work_user_init__extern(struct k_work_user *work, k_work_user_handler_t handler) { k_work_user_init(work, handler); }
bool k_work_user_is_pending__extern(struct k_work_user *work) { return k_work_user_is_pending(work); }
int k_work_user_submit_to_queue__extern(struct k_work_user_q *work_q, struct k_work_user *work) { return k_work_user_submit_to_queue(work_q, work); }
k_tid_t k_work_user_queue_thread_get__extern(struct k_work_user_q *work_q) { return k_work_user_queue_thread_get(work_q); }
int k_msgq_alloc_init__extern(struct k_msgq *msgq, size_t msg_size, uint32_t max_msgs) { return k_msgq_alloc_init(msgq, msg_size, max_msgs); }
int k_msgq_put__extern(struct k_msgq *msgq, const void *data, k_timeout_t timeout) { return k_msgq_put(msgq, data, timeout); }
int k_msgq_get__extern(struct k_msgq *msgq, void *data, k_timeout_t timeout) { return k_msgq_get(msgq, data, timeout); }
int k_msgq_peek__extern(struct k_msgq *msgq, void *data) { return k_msgq_peek(msgq, data); }
int k_msgq_peek_at__extern(struct k_msgq *msgq, void *data, uint32_t idx) { return k_msgq_peek_at(msgq, data, idx); }
void k_msgq_purge__extern(struct k_msgq *msgq) { k_msgq_purge(msgq); }
uint32_t k_msgq_num_free_get__extern(struct k_msgq *msgq) { return k_msgq_num_free_get(msgq); }
void k_msgq_get_attrs__extern(struct k_msgq *msgq, struct k_msgq_attrs *attrs) { k_msgq_get_attrs(msgq, attrs); }
uint32_t z_impl_k_msgq_num_free_get__extern(struct k_msgq *msgq) { return z_impl_k_msgq_num_free_get(msgq); }
uint32_t k_msgq_num_used_get__extern(struct k_msgq *msgq) { return k_msgq_num_used_get(msgq); }
uint32_t z_impl_k_msgq_num_used_get__extern(struct k_msgq *msgq) { return z_impl_k_msgq_num_used_get(msgq); }
int k_pipe_alloc_init__extern(struct k_pipe *pipe, size_t size) { return k_pipe_alloc_init(pipe, size); }
int k_pipe_put__extern(struct k_pipe *pipe, void *data, size_t bytes_to_write, size_t *bytes_written, size_t min_xfer, k_timeout_t timeout) { return k_pipe_put(pipe, data, bytes_to_write, bytes_written, min_xfer, timeout); }
int k_pipe_get__extern(struct k_pipe *pipe, void *data, size_t bytes_to_read, size_t *bytes_read, size_t min_xfer, k_timeout_t timeout) { return k_pipe_get(pipe, data, bytes_to_read, bytes_read, min_xfer, timeout); }
size_t k_pipe_read_avail__extern(struct k_pipe *pipe) { return k_pipe_read_avail(pipe); }
size_t k_pipe_write_avail__extern(struct k_pipe *pipe) { return k_pipe_write_avail(pipe); }
void k_pipe_flush__extern(struct k_pipe *pipe) { k_pipe_flush(pipe); }
void k_pipe_buffer_flush__extern(struct k_pipe *pipe) { k_pipe_buffer_flush(pipe); }
uint32_t k_mem_slab_num_used_get__extern(struct k_mem_slab *slab) { return k_mem_slab_num_used_get(slab); }
uint32_t k_mem_slab_max_used_get__extern(struct k_mem_slab *slab) { return k_mem_slab_max_used_get(slab); }
uint32_t k_mem_slab_num_free_get__extern(struct k_mem_slab *slab) { return k_mem_slab_num_free_get(slab); }
int k_poll__extern(struct k_poll_event *events, int num_events, k_timeout_t timeout) { return k_poll(events, num_events, timeout); }
void k_poll_signal_init__extern(struct k_poll_signal *sig) { k_poll_signal_init(sig); }
void k_poll_signal_reset__extern(struct k_poll_signal *sig) { k_poll_signal_reset(sig); }
void k_poll_signal_check__extern(struct k_poll_signal *sig, unsigned int *signaled, int *result) { k_poll_signal_check(sig, signaled, result); }
int k_poll_signal_raise__extern(struct k_poll_signal *sig, int result) { return k_poll_signal_raise(sig, result); }
void k_cpu_idle__extern(void) { k_cpu_idle(); }
void k_cpu_atomic_idle__extern(unsigned int key) { k_cpu_atomic_idle(key); }
void k_str_out__extern(char *c, size_t n) { k_str_out(c, n); }
int k_float_disable__extern(struct k_thread *thread) { return k_float_disable(thread); }
int k_float_enable__extern(struct k_thread *thread, unsigned int options) { return k_float_enable(thread, options); }
int k_thread_stack_space_get__extern(const struct k_thread *thread, size_t *unused_ptr) { return k_thread_stack_space_get(thread, unused_ptr); }
void k_thread_deadline_set__extern(k_tid_t thread, int deadline) { k_thread_deadline_set(thread, deadline); }
int k_futex_wait__extern(struct k_futex *futex, int expected, k_timeout_t timeout) { return k_futex_wait(futex, expected, timeout); }
int k_futex_wake__extern(struct k_futex *futex, bool wake_all) { return k_futex_wake(futex, wake_all); }
