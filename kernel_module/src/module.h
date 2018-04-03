#ifndef _KIKI_H_
#define _KIKI_H_

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>

#include <linux/init.h>

#include <linux/device.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#include <linux/string.h>
#include <linux/list.h>
#include <linux/delay.h>

#include <linux/slab.h>

#include <linux/time.h>


#ifndef time_t
typedef long time_t;
#endif

#include "kiki.h"

/*
  not given to contestants
*/
#include "correction_stats_struct.h"

#define KIKIIO_CORRECTION_STATS 0x28a
#define KIKIIO_RESET_CORRECTION_STATS 0x28b

extern struct kiki_correction_stats correction_stats;

void kiki_correction_stats_init(void);
void kiki_correction_stats_reset(void);

#define CS_CORRECTION_MODE 1


/*
  Kiki specific variables
*/
#define KIKI_DEVICE_NAME "kiki"
#define KIKI_DEVICE_CLASS_NAME "kikidev"

/*
  module variables first
*/
extern int device_major_number; /* character device major number */
extern struct class *device_class; /* character device driver-driven class */
extern struct device *device; /* pointer to device */
extern struct mutex mutex;

/*
  File operations table for the character device
*/
extern struct file_operations file_operations;


/*
  Buffer and buffer list
 */
struct kiki_buffer {
  unsigned long id;
  unsigned long length;
  void *data;

  time_t time_created;
  time_t time_accessed;
};

#define KIKI_BUFFER_MAX_LEN 2048

struct kiki_buffer *buffer_new(unsigned long id, unsigned long size);
void buffer_free(struct kiki_buffer *buf);

void buffer_list_init(void);
void buffer_touch(struct kiki_buffer *buf);
int buffer_list_append(struct kiki_buffer *buf);
int buffer_id_present(unsigned long id);
struct kiki_buffer *buffer_get(unsigned long id);
unsigned long buffer_list_count(void);
int buffer_list_foreach(int (*callback)(struct kiki_buffer *, void *), void *data);
void buffer_list_clear(void);


void buffer_select(unsigned long id);
int buffer_selection(unsigned long *id);
void buffer_clear_selection(void);


/*
  Called almost everywhere, tells whether it should fail or not
 */
int random_fail(void);


/*
  Device current status (or error state)
 */
extern struct kiki_status status_;
unsigned int get_status(void);
void set_status(unsigned int no, const char *msg);
void reset_status(void);


/*
  Device state
 */
int get_state(void);
void set_state(int state);
void reset_state(void);


/*
  Reset the whole device (called in deinit)
 */
void reset_device(void);


#endif
