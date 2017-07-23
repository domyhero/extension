#include "../../common.h"

#include "../parameters.h"
#include "../arginfo.h"

#include "../handlers/php_pair_handlers.h"

#include "php_pair_ce.h"

#define METHOD(name) PHP_METHOD(Pair, name)

zend_class_entry *php_ds_pair_ce;

METHOD(__construct)
{
    PARSE_OPTIONAL_ZVAL_OPTIONAL_ZVAL(key, value);
    {
        ds_pair_t *pair = THIS_DS_PAIR();

        if (key) {
            ZVAL_COPY(&pair->key, key);
        } else {
            ZVAL_NULL(&pair->key);
        }

        if (value) {
            ZVAL_COPY(&pair->value, value);
        } else {
            ZVAL_NULL(&pair->value);
        }
    }
}

METHOD(copy)
{
    PARSE_NONE;
    RETURN_DS_PAIR(ds_pair_clone(THIS_DS_PAIR()));
}

METHOD(toArray)
{
    PARSE_NONE;
    ds_pair_to_array(THIS_DS_PAIR(), return_value);
}

METHOD(jsonSerialize)
{
    PARSE_NONE;
    ds_pair_to_array(THIS_DS_PAIR(), return_value);
}

void php_ds_register_pair()
{
    zend_class_entry ce;

    zend_function_entry methods[] = {
        PHP_DS_ME(Pair, __construct)
        PHP_DS_ME(Pair, copy)
        PHP_DS_ME(Pair, jsonSerialize)
        PHP_DS_ME(Pair, toArray)
        PHP_FE_END
    };

    INIT_CLASS_ENTRY(ce, PHP_DS_NS(Pair), methods);
    php_ds_pair_ce = zend_register_internal_class(&ce);

    php_ds_pair_ce->ce_flags         |= ZEND_ACC_FINAL;
    php_ds_pair_ce->create_object     = php_ds_pair_create_object;
    php_ds_pair_ce->serialize         = php_ds_pair_serialize;
    php_ds_pair_ce->unserialize       = php_ds_pair_unserialize;

    zend_class_implements(php_ds_pair_ce, 1, php_json_serializable_ce);
    php_ds_register_pair_handlers();
}
