#ifndef _KIKI_IOCTL_H_
#define _KIKI_IOCTL_H_

/*
  List of ioctls for the kiki device
 */
#define KIKIIO_GETSTATUS 0x1001
#define KIKIIO_REQBUF    0x1002
#define KIKIIO_LISTBUF   0x1003
#define KIKIIO_COUNTBUF  0x1004
#define KIKIIO_SELBUF    0x1008
#define KIKIIO_FILLBUF   0x1010
#define KIKIIO_INSPBUF   0x1020
#define KIKIIO_DUMPBUF   0x1040
#define KIKIIO_CLRBUFS   0x1080

#define KIKIIO_WAITPRCWORK 0x1400
#define KIKIIO_IOINFO      0x1800

#define KIKIIO_GETSTATE    0x4000
#define KIKIIO_SETSTATELIS 0x8000
#define KIKIIO_SETSTATEANS 0x10000

#define KIKIIO_DO_NOT_CALL 0x29a
#define KIKIIO_RST         0x29b


/*
  Status object for kiki device
 */
struct kiki_status {
  int status_no;
  char status_msg[1024];
};

/*
  Request object to be passed to reqbuf
 */
struct kiki_buffer_request {
  unsigned long id;
  unsigned long size;
};

/*
  Filling request object to be passed to fillbuf
 */
struct kiki_buffer_fill_request {
  unsigned long length;
  void *data;
};


/*
  buffer information returned for inspection
 */
struct kiki_buffer_info {
  unsigned long id;
  unsigned long length;
  long time_created;
  long time_accessed;
};


/*
  Device statuses NORMAL and then ERRORS
 */
#define KIKIST_IDLE             0x0
#define KIKIST_BUFSELECTED      0x100

#define KIKIERR_FAILED_REQBUF   0x1
#define KIKIERR_FAILED_LISTBUF  0x2
#define KIKIERR_FAILED_COUNTBUF 0x3
#define KIKIERR_FAILED_CLRBUF   0x4
#define KIKIERR_FAILED_SELBUF   0x5
#define KIKIERR_FAILED_FILLBUF  0x6
#define KIKIERR_FAILED_DUMPBUF  0x7
#define KIKIERR_FAILED_INSPBUF  0x8
#define KIKIERR_FAILED_IOINFO   0x9
#define KIKIERR_FAILED_SETSTATE 0xa


/*
  Device states
 */
#define KIKI_STATENIL 0x0
#define KIKI_STATELIS 0x1
#define KIKI_STATEANS 0x2


#endif
