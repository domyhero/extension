#ifndef PHP_DS_PRIORITY_QUEUE_HANDLERS_H
#define PHP_DS_PRIORITY_QUEUE_HANDLERS_H

#include "php.h"

extern zend_object_handlers php_ds_priority_queue_handlers;

void php_ds_register_priority_queue_handlers();

#endif