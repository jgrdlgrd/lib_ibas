//
// Created by Павел on 15.04.2017.
//

#pragma once

#define $_field(type, name, value...) type name;
#define $_field_def(type, name, value...) value,

#define $_method(ret, name, args...) ret (*name)($class_t self, ## args);
#define $_method_def(ret, name, args...) $ns(name),

#define $_static(ret, name, args...) ret (*name)(args);
#define $_static_def(ret, name, args...) $sns(name),

#define disposeObj(obj, failed) Object.destroy(obj);
#define withObj(type, obj) type obj = NULL; with(obj, disposeObj)

//FIXME
#define ensureClass(obj, class) if (Ibas.getClass(obj) != class##_class) throw(ClassCastException, NULL)

#define $call(obj, method) obj->_class->vtable->method(obj $call1
#define $call1(args...) , ## args)

#define $this(method) $call(self, method)
#define $super(method) self->_class->superClass->vtable->method(self $call1

//FIXME
#define $callI(obj) ((interface##_i)(Ibas.getImpl(obj, #interface)))->method

#define $name_t(name) $paste(name, _t)
#define $name_s(name) $paste(name, _s)
#define $$name_static(name) $paste3($, name, _static)
#define $$name_fields(name) $paste3($, name, _fields)
#define $$name_methods(name) $paste3($, name, _methods)
#define $name_klass_t(name) $paste(name, _klass_t)
#define $name_klass(name) $paste(name, _klass)
#define $name_static_t(name) $paste(name, _static_t)
#define $name_static(name) name
#define $name_vtable_t(name) $paste(name, _vtable_t)
#define $name_vtable(name) $paste(name, _vtable)

#define $class_t $name_t($class)
#define $class_s $name_s($class)
#define $$class_static $$name_static($class)
#define $$class_fields $$name_fields($class)
#define $$class_methods $$name_methods($class)
#define $class_klass_t $name_klass_t($class)
#define $class_klass $name_klass($class)
#define $class_static_t $name_static_t($class)
#define $class_static $name_static($class)
#define $class_vtable_t $name_vtable_t($class)
#define $class_vtable $name_vtable($class)

#define $ns(name) $paste3(__, $class, _##name)
#define $sns(name) $paste3(__, $class, _s_##name)

#define $declareClass(name) $declareClass1(name, struct $name_s(name))
#define $declareClass1(name, base) \
    typedef base $name_s(name); \
    typedef struct $name_vtable_t(name) $name_vtable_t(name); \
    typedef struct $name_klass_t(name) $name_klass_t(name); \
    typedef $name_s(name)* $name_t(name)

#define $declareInterface(name) \
    typedef Object_t $name_t(name); \
    typedef struct $name_vtable_t(name) $name_vtable_t(name);

#define $defineInterface(args...) \
    struct $class_vtable_t {$$class_methods($_method, ## args)}

#define $declareFields(args...) struct $class_s {$class_klass_t *_class; $$class_fields($_field, $_static, ## args)}

#define $declareStatic(args...) \
    typedef struct $class_static_t {$$class_static($_field, $_static, ## args)} $class_static_t; \
    extern $class_static_t $class_static

#define $defineStatic(args...) \
    $class_static_t $class_static = {$$class_static($_field_def, $_static_def, ## args)}

#define $declareMethods(args...) \
    struct $class_vtable_t {$$class_methods($_method, ## args)}; \
    extern struct $class_vtable_t $class_vtable; \
    extern Pointer $class_klass[]

#define $defineMethods(args...) \
    $class_vtable_t $class_vtable = {$$class_methods($_method_def, ## args)}

#define $defineClass(super) \
    struct $class_klass_t {$class_vtable_t *vtable; $name_klass_t(super) *superClass;}; \
    $defineClass1(&$name_klass(super))
#define $defineClass1(super_klass) Pointer $class_klass[] = {&$class_vtable, super_klass, $str($class) $defineClass2
#define $defineClass2(interfaces...) , ## interfaces, NULL}

#define $implements(interface, offset) #interface, (void **) &$class_vtable + (offset)

#define $constructor $constructor1
#define $constructor1(name) $class_t $sns(name) $constructor2
#define $constructor2(args...) (args) {$class_t self = NULL; $constructor3
#define $constructor3(body...) body return self;}

#define $setClass(obj, class) obj->_class = ($name_klass_t(class) *) $name_klass(class)
#define $construct self = Ibas.alloc(sizeof($class_s), NULL); $setClass(self, $class)

#define $public $public1
#define $public1(name) $ns(name) $public2
#define $public2(args...) ($class_t self, ## args) {$public3
#define $public3(body...) body}

#define $private $public

#define $static $static1
#define $static1(name) $sns(name) $static2
#define $static2(args...) (args) {; $static3
#define $static3(body...) body}

#define $privateStatic $static
