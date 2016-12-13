twoton_Fi: mov 1, %g2
           cmp %o0, 0
           ble .LL3
.LL4:      add %o0, -1, %o0
           sll %g2, 1, %g2
           cmp %o0, 0
           bg  .LL4
.LL3:      mov %g2, %o0
           retl
