/* 
 *** Try Kernel
 *      タスク付属同期機能
*/

#include <trykernel.h>
#include <knldef.h>

/* タスクの実行遅延 API */
ER tk_dly_tsk( RELTIM dlytim )
{
    UINT    intsts;
    ER      err = E_OK;

    DI(intsts);     // 割込みの禁止
    if(dlytim > 0) {
        tqueue_remove_top(&ready_queue[cur_task->itskpri]); // タスクをレディキューから外す

        /* TCBの各種情報を変更する */
        cur_task->state   = TS_WAIT;                // タスクの状態を待ち状態に変更
        cur_task->waifct  = TWFCT_DLY;              // 待ち要因を設定
        cur_task->waitim  = dlytim + TIMER_PERIOD;  // 待ち時間を設定
        cur_task->waierr = &err;                   // 待ち解除時のエラーコード

        tqueue_add_entry(&wait_queue, cur_task);    // タスクをウェイトキューに繋ぐ
        scheduler();                                // スケジューラの実行
    }
    EI(intsts);     // 割込みの許可
    return err;
}

ER tk_slp_tsk(TMO tmout)
{
    UINT   intsts;
    ER     err = E_OK;
    
    DI(intsts);
    if (cur_tsk->wupcnt > 0){
        cur_tsk->wupcnt--;
    }else{
        tqueue_remove_top(&ready_queue[cur_task->itskpri]);

        /**/
        cur_task->state = TS_WAIT;
        cur_task->waifct = TWFCT_SLP;
        cur_task->waitim = (tmout==TMO_FEVR)?tmout:(tmout+TIMER_PERIOD);
        cur_task->waierr = &err;

        tqueue_add_entry(&wait_queue, cur_task);
        scheduler();
    }
    EI(intsts); 
    return err;
}

ER tk_wup_task(ID tskid)
{
    TCB     *tcb;
    UINT    intsts;
    ER  err = E_OK;

    if (tskid <= 0 || tskid > CNF_MAX_TSKID){
      return E_ID;
    }

    DI(intsts);
    tcb = &tcb_tbl[tskid-1];
    if ((tcb->state == TS_WAIT) && 
        (tcb->waifct == TWFCT_SLP)){
            tqueue_remove_entry(&wait_queue, tcb);
            tcb->state = TS_READY;
            tcb->waifct = TWFCT_NON;
            tqueue_add_entry(&ready_queue[tcb->itskpri],tcb);
            scheduler();
    } else if (tcb->state == TS_READY || tcb->waifct == TS_WAIT ){
        tcb-> wupcnt++;
    } else{
        err = E_OBJ;
    }

    EI(intsts);
    return err;
}   