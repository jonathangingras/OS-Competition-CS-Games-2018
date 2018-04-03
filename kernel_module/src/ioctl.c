#include "module.h"

int kiki_wait_proc_work(unsigned int no, void *data);
int kiki_do_not_call(unsigned int no, void *data);

int kiki_get_status(unsigned int no, void *data);
int kiki_reqbuf(unsigned int no, void *data);
int kiki_listbuf(unsigned int no, void *data);
int kiki_countbuf(unsigned int no, void *data);
int kiki_selbuf(unsigned int no, void *data);
int kiki_clearbufs(unsigned int no, void *data);
int kiki_fillbuf(unsigned int no, void *data);
int kiki_dumpbuf(unsigned int no, void *data);
int kiki_inspbuf(unsigned int no, void *data);
int kiki_ioinfo(unsigned int no, void *data);
int kiki_getstate(unsigned int no, void *data);
int kiki_setstatelis(unsigned int no, void *data);
int kiki_setstateans(unsigned int no, void *data);
int kiki_reset(unsigned int no, void *data);

int kiki_correction_stats(unsigned int no, void *data);
int kiki_reset_correction_stats(unsigned int no, void *data);


static int null_ioctl(unsigned int no, void *data) {
  printk(KERN_INFO "kiki: null ioctl called, no:%u\n", no);
  return 0;
}

static unsigned int ioctl_nos[] = {
  KIKIIO_GETSTATUS,
  KIKIIO_REQBUF,
  KIKIIO_LISTBUF,
  KIKIIO_COUNTBUF,
  KIKIIO_SELBUF,
  KIKIIO_FILLBUF,
  KIKIIO_INSPBUF,
  KIKIIO_DUMPBUF,
  KIKIIO_CLRBUFS,

  KIKIIO_WAITPRCWORK,
  KIKIIO_IOINFO,

  KIKIIO_GETSTATE,
  KIKIIO_SETSTATELIS,
  KIKIIO_SETSTATEANS,

  KIKIIO_DO_NOT_CALL,
  KIKIIO_RST,

  KIKIIO_CORRECTION_STATS,
  KIKIIO_RESET_CORRECTION_STATS,
};

static int (* ioctl_defs[sizeof(ioctl_nos)/sizeof(unsigned int)])(unsigned int, void*) = {
  kiki_get_status,
  kiki_reqbuf,
  kiki_listbuf,
  kiki_countbuf,
  kiki_selbuf,
  kiki_fillbuf,
  kiki_inspbuf,
  kiki_dumpbuf,
  kiki_clearbufs,

  kiki_wait_proc_work,
  kiki_ioinfo,

  kiki_getstate,
  kiki_setstatelis,
  kiki_setstateans,

  kiki_do_not_call,
  kiki_reset,

  kiki_correction_stats,
  kiki_reset_correction_stats,
};


int call_ioctl(int ioctl_no, void *data) {
  int i;
  for(i = 0; i < sizeof(ioctl_nos)/sizeof(unsigned int); ++i) {
    if(ioctl_nos[i] == ioctl_no) {
      return ioctl_defs[i](ioctl_no, data);
    }
  }
  return null_ioctl(ioctl_no, data);
}


long dev_ioctl(struct file *file, unsigned int cmd, unsigned long subcmd) {
  int err = 0;

  printk(KERN_INFO "kiki: IOCTL: %u, %lu\n", cmd, subcmd);

  if((err = call_ioctl(cmd, (void *)subcmd))) {
    printk(KERN_ALERT "kiki: there was an error with the ioctl %u\n", cmd);
    return err;
  }

  return 0;
}
