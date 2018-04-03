#include "module.h"


struct kiki_buffer_list {
  struct kiki_buffer *buf;
  struct list_head list;
};

static struct kiki_buffer_list buffer_list = {
  .buf = NULL
};
static unsigned long buffer_count = 0;


struct kiki_buffer *buffer_new(unsigned long id, unsigned long size) {
  struct timespec now;
  struct kiki_buffer *buf = kmalloc(sizeof(struct kiki_buffer), GFP_KERNEL);

  if(!buf || size == 0) {
    return NULL;
  }

  // main fields
  buf->id = id;
  buf->data = kmalloc(size, GFP_KERNEL);
  if(!buf->data) {
    kfree(buf);
    return NULL;
  }
  buf->length = size;

  // info
  getnstimeofday(&now);
  buf->time_created = now.tv_sec;
  buf->time_accessed = now.tv_sec;

  return buf;
}


void buffer_touch(struct kiki_buffer *buf) {
  struct timespec now;

  getnstimeofday(&now);
  buf->time_accessed = now.tv_sec;
}


void buffer_free(struct kiki_buffer *buf) {
  kfree(buf->data);
  kfree(buf);
}


void buffer_list_init(void) {
  INIT_LIST_HEAD(&(buffer_list.list));
}


static int is_the_id(struct kiki_buffer *buf, void *id) {
  return buf->id == *(unsigned long*)id;
}

int buffer_id_present(unsigned long id) {
  unsigned long id_ = id;
  return buffer_list_foreach(is_the_id, &id_);
}


struct buffer_finder {
  unsigned long id;
  struct kiki_buffer *output;
};

static int find_buffer_by_id(struct kiki_buffer *buf, void *_finder) {
  struct buffer_finder *finder;

  finder = _finder;

  if(buf->id == finder->id) {
    finder->output = buf;
    return 1;
  }

  return 0;
}

struct kiki_buffer *buffer_get(unsigned long id) {
  struct buffer_finder finder;

  finder.output = NULL;
  finder.id = id;

  buffer_list_foreach(find_buffer_by_id, &finder);

  return finder.output;
}

int buffer_list_append(struct kiki_buffer *buf) {
  struct kiki_buffer_list *element;

  if(!buf) {
    return -1;
  }

  if(buffer_id_present(buf->id)) {
    return -2;
  }

  element = kmalloc(sizeof(struct kiki_buffer_list), GFP_KERNEL);
  if(!element) {
    return -3;
  }

  element->buf = buf;

  list_add(&(element->list), &(buffer_list.list));

  buffer_count++;

  return 0;
}

int buffer_list_foreach(int (*callback)(struct kiki_buffer *, void *), void *data) {
  struct list_head *position;

  list_for_each(position, &(buffer_list.list)) {
    struct kiki_buffer_list *entry;
    int err;

    entry = list_entry(position, struct kiki_buffer_list, list);

    err = 0;
    if((err = callback(entry->buf, data))) {
      return err;
    }
  }

  return 0;
}

static int buffer_list_count_accumulate(struct kiki_buffer *buf, void *counter) {
  ++*((unsigned long *)counter);
  return 0;
}

unsigned long buffer_list_count(void) {
  unsigned long counter = 0;
  buffer_list_foreach(buffer_list_count_accumulate, &counter);
  return counter;
}

void buffer_list_clear(void) {
  struct list_head *position, *q;
  struct kiki_buffer_list *tmp;

  if(list_empty(&buffer_list.list)) {
    return;
  }

  list_for_each_safe(position, q, &(buffer_list.list)){
    tmp = list_entry(position, struct kiki_buffer_list, list);
    list_del(position);
    buffer_free(tmp->buf);
    kfree(tmp);
  }

  buffer_count = 0;
}
