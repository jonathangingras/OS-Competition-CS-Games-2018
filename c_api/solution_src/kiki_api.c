#include "kiki_api.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>


struct kiki_handle_t {
  int fd;
};

struct kiki_buffer_handle_t {
  unsigned long id;
  struct kiki_handle_t *device;
};


int kiki_device_init(kiki_handle_t **dev) {
  kiki_handle_t *out = NULL;
  int fd;

  out = malloc(sizeof(kiki_handle_t));

  if(!out) {
    return -1;
  }

  fd = open("/dev/kiki", O_RDWR);

  if(fd < 0) {
    free(out);
    return -2;
  }

  *dev = out;
  (*dev)->fd = fd;

  return 0;
}

void kiki_device_deinit(kiki_handle_t *dev) {
  close(dev->fd);
  free(dev);
}

int kiki_device_fileno(kiki_handle_t *dev) {
  return dev->fd;
}

int kiki_device_get_status(kiki_handle_t *dev, struct kiki_status *out) {
  int ret;

  ret = ioctl(dev->fd, KIKIIO_GETSTATUS, out);

  return ret;
}

static int check_fd_valid(int fd) {
  return fd > 0;
}

int kiki_device_clear_buffers(kiki_handle_t *dev) {
  int ret;

  if(!check_fd_valid(dev->fd)) {
    return -1;
  }

  do {
    ret = ioctl(dev->fd, KIKIIO_CLRBUFS);
  } while(ret);

  return 0;
}

int kiki_count_buffers(kiki_handle_t *dev, size_t *amount) {
  unsigned long count;
  int ret;

  do {
    ret = ioctl(dev->fd, KIKIIO_COUNTBUF, &count);
  } while(ret);

  *amount = count;

  return 0;
}

int kiki_list_buffers(kiki_handle_t *dev, kiki_buffer_handle_t ***buffers) {
  unsigned long *ids = NULL;
  kiki_buffer_handle_t *aligned_outputs;
  kiki_buffer_handle_t **outputs;
  size_t amount;
  int ret;
  size_t i;

  if((ret = kiki_count_buffers(dev, &amount))) {
    return ret;
  }

  if(amount == 0) {
    *buffers = NULL;
    return 0;
  }

  ids = malloc(amount * sizeof(unsigned long));
  if(!ids) {
    return -1;
  }

  outputs = malloc(amount * sizeof(kiki_buffer_handle_t *));
  if(!outputs) {
    free(ids);
    return -2;
  }

  aligned_outputs = malloc(amount * sizeof(kiki_buffer_handle_t));
  if(!aligned_outputs) {
    free(ids);
    free(outputs);
    return -3;
  }

  do {
    ret = ioctl(dev->fd, KIKIIO_LISTBUF, ids);
  } while(ret);

  for(i = 0; i < amount; ++i) {
    outputs[i] = aligned_outputs + i;
    outputs[i]->id = ids[i];
  }

  *buffers = outputs;

  free(ids);
  return 0;
}

void kiki_buffer_list_free(kiki_buffer_handle_t **buffers) {
  if(buffers != NULL) {
    free(buffers[0]);
  }
  free(buffers);
}

int kiki_new_buffer_manual(kiki_handle_t *dev, size_t size, kiki_buffer_handle_t **buffer, unsigned long new_id) {
  struct kiki_buffer_request request;
  int ret;

  request.size = size;
  request.id = new_id;

  do {
    ret = ioctl(dev->fd, KIKIIO_REQBUF, &request);
  } while(ret);

  *buffer = malloc(sizeof(kiki_buffer_handle_t));
  (*buffer)->id = request.id;
  (*buffer)->device = dev;

  return 0;
}

int kiki_new_buffer(kiki_handle_t *dev, size_t size, kiki_buffer_handle_t **buffer) {
  struct kiki_buffer_request request;
  size_t buffer_count;
  kiki_buffer_handle_t **buffer_list;
  unsigned long new_id = 0;
  size_t i;
  int ret;

  request.size = size;

  if((ret = kiki_count_buffers(dev, &buffer_count))) {
    return -1;
  }
  if((ret = kiki_list_buffers(dev, &buffer_list))) {
    return -2;
  }

  /* find a new id by choosing max existing + 1 */
  for(i = 0; i < buffer_count; ++i) {
    if(new_id < buffer_list[i]->id) {
      new_id = buffer_list[i]->id;
    }
  }

  return kiki_new_buffer_manual(dev, size, buffer, new_id + 1);
}

unsigned long kiki_buffer_id(kiki_buffer_handle_t *buffer) {
  return buffer->id;
}

int kiki_buffer_inspect(kiki_buffer_handle_t *buffer, struct kiki_buffer_info *info) {
  int ret;

  do {
    do {
      ret = ioctl(buffer->device->fd, KIKIIO_SELBUF, buffer->id);
    } while(ret);

    ret = ioctl(buffer->device->fd, KIKIIO_INSPBUF, info);
  } while(ret);

  return 0;
}

int kiki_buffer_size(kiki_buffer_handle_t *buffer, size_t *out) {
  struct kiki_buffer_info info;
  int ret;

  if((ret = kiki_buffer_inspect(buffer, &info))) {
    return -1;
  }

  *out = info.length;

  return 0;
}

ssize_t kiki_write_buffer(kiki_buffer_handle_t *buffer, const char *data, size_t length) {
  struct kiki_buffer_fill_request request;
  int ret;
  size_t max_size = 0;

  request.data = (void *)data;
  request.length = length;

  if(kiki_buffer_size(buffer, &max_size)) {
    return -1;
  }

  if(length > max_size) {
    return -2;
  }

  do {
    do {
      do {
        ret = ioctl(buffer->device->fd, KIKIIO_SELBUF, buffer->id);
      } while(ret);

      ret = ioctl(buffer->device->fd, KIKIIO_SETSTATELIS);
    } while(ret);

    ret = ioctl(buffer->device->fd, KIKIIO_FILLBUF, &request);
  } while(ret);

  return length;
}

ssize_t kiki_read_buffer(kiki_buffer_handle_t *buffer, char *data, size_t length) {
  int ret;
  size_t size;

  if(kiki_buffer_size(buffer, &size)) {
    return -1;
  }

  if(length > size) {
    return -2;
  }

  do {
    do {
      do {
        ret = ioctl(buffer->device->fd, KIKIIO_SELBUF, buffer->id);
      } while(ret);

      ret = ioctl(buffer->device->fd, KIKIIO_SETSTATEANS);
    } while(ret);

    ret = ioctl(buffer->device->fd, KIKIIO_DUMPBUF, data);
  } while(ret);

  return length;
}

int kiki_save_buffer(kiki_buffer_handle_t *buffer, FILE *output) {
  int err;
  size_t size;
  unsigned long id;
  void *data;

  if((err = kiki_buffer_size(buffer, &size))) {
    return -1;
  }

  id = kiki_buffer_id(buffer);

  data = malloc(size);
  if(!data) {
    return -2;
  }

  if((err = kiki_read_buffer(buffer, data, size)) != size) {
    free(data);
    return -3;
  }

  fprintf(output, "%zu\n%zu\n", id, size);

  if(fwrite(data, 1, size, output) != size) {
    free(data);
    return -4;
  }

  fflush(output);

  free(data);
  return 0;
}

int kiki_load_buffer(kiki_handle_t *dev, kiki_buffer_handle_t **out, FILE *input) {
  int err;
  size_t size;
  unsigned long id;
  void *data;

  fscanf(input, "%zu\n%zu\n", &id, &size);

  data = malloc(size);
  if(!data) {
    return -1;
  }

  if(fread(data, 1, size, input) != size) {
    free(data);
    return -2;
  }

  if(kiki_new_buffer_manual(dev, size, out, id)) {
    free(data);
    return -3;
  }

  free(data);
  return 0;
}
