//
// Created by HenryRenYz on 2021/2/26.
//

#ifndef __CREFLECTION_UTIL_INC__
#define __CREFLECTION_UTIL_INC__

#include <jni.h>

#define ENV (*env)->
#define ELE_OF(_array, _index) ENV GetObjectArrayElement(env, _array, _index)
#define LENGTH_OF(_array) ENV GetArrayLength(env, _array)
#define FIELD_ID(_cls, _name, _sig) ENV GetFieldID(env, _cls, _name, _sig)
#define STATIC_FIELD_ID(_cls, _name, _sig) ENV GetStaticFieldID(env, _cls, _name, _sig)
#define GET_FIELD_OBJ(_obj, _id) ENV GetObjectField(env, _obj, _id)
#define GET_STATIC_FIELD_OBJ(_cls, _id) ENV GetStaticObjectField(env, _cls, _id)
#define GET_CLASS(_obj) ENV GetObjectClass(env, _obj)

#define synchronized(_jobject)      \
ENV MonitorEnter(env, _jobject);    \
for (jboolean jboolSwitch = TRUE; jboolSwitch; jboolSwitch = FALSE, ENV MonitorExit(env, _jobject))

#define GLOBAL_REF(_Item) (jclass) (*env)->NewGlobalRef(env, _Item)
#define GLOBAL_REF_CLASS(_name) GLOBAL_REF(ENV FindClass(env, #_name))

#define FALSE JNI_FALSE
#define TRUE JNI_TRUE

#define __GLOBAL__

#define MODIFIER_PUBLIC         0x00000001
#define MODIFIER_PRIVATE        0x00000002
#define MODIFIER_PROTECTED      0x00000004
#define MODIFIER_STATIC         0x00000008
#define MODIFIER_FINAL          0x00000010
#define MODIFIER_SYNCHRONIZED   0x00000020
#define MODIFIER_VOLATILE       0x00000040
#define MODIFIER_TRANSIENT      0x00000080
#define MODIFIER_NATIVE         0x00000100
#define MODIFIER_INTERFACE      0x00000200
#define MODIFIER_ABSTRACT       0x00000400
#define MODIFIER_STRICT         0x00000800

// Non-public
#define MODIFIER_BRIDGE         0x00000040
#define MODIFIER_VARARGS        0x00000080
#define MODIFIER_SYNTHETIC      0x00001000
#define MODIFIER_ANNOTATION     0x00002000
#define MODIFIER_ENUM           0x00004000
#define MODIFIER_MANDATED       0x00008000

extern jobject      LOCK;
extern jboolean     initialized;

extern jclass       Method;
extern jclass       Field;
extern jclass       Constructor;

extern jfieldID     Method_parameterTypes;
extern jfieldID     Method_returnType;
extern jfieldID     Method_clazz;
extern jfieldID     Method_modifiers;
extern jfieldID     Field_type;
extern jfieldID     Field_clazz;
extern jfieldID     Field_modifiers;
extern jfieldID     Constructor_clazz;
extern jfieldID     Constructor_parameterTypes;

extern jclass       Class;
extern jclass       Object;
extern jmethodID    Object_toString;
extern jmethodID    Object_hashCode;

extern jclass       Integer;
extern jint         Integer_hash;
extern jint         __int_hash__;
extern jclass       __int__;
extern jfieldID     Integer_value;
extern jmethodID    Integer_valueOf;

extern jclass       Short;
extern jint         Short_hash;
extern jint         __short_hash__;
extern jclass       __short__;
extern jfieldID     Short_value;
extern jmethodID    Short_valueOf;

extern jclass       Long;
extern jint         Long_hash;
extern jint         __long_hash__;
extern jclass       __long__;
extern jfieldID     Long_value;
extern jmethodID    Long_valueOf;

extern jclass       Byte;
extern jint         Byte_hash;
extern jint         __byte_hash__;
extern jclass       __byte__;
extern jfieldID     Byte_value;
extern jmethodID    Byte_valueOf;

extern jclass       Float;
extern jint         Float_hash;
extern jint         __float_hash__;
extern jclass       __float__;
extern jfieldID     Float_value;
extern jmethodID    Float_valueOf;

extern jclass       Double;
extern jint         Double_hash;
extern jint         __double_hash__;
extern jclass       __double__;
extern jfieldID     Double_value;
extern jmethodID    Double_valueOf;

extern jclass       Character;
extern jint         Character_hash;
extern jint         __char_hash__;
extern jclass       __char__;
extern jfieldID     Character_value;
extern jmethodID    Character_valueOf;

extern jclass       Boolean;
extern jint         Boolean_hash;
extern jint         __boolean_hash__;
extern jclass       __boolean__;
extern jfieldID     Boolean_value;
extern jmethodID    Boolean_valueOf;

extern jclass       Void;
extern jint         Void_hash;
extern jint         __void_hash__;
extern jclass       __void__;

extern jclass       RuntimeException;
extern jclass       IllegalArgumentException;
extern jclass       NullPointerException;
extern jmethodID    newRuntimeException;

jboolean INIT(JNIEnv * env);

typedef struct Node * Node;
struct Node {
    Node    prev;
    void *  key;
    void *  value;
    Node    next;
};

typedef struct Queue {
    Node    start;
    Node    end;
    int     size;
} Queue;

void queue_add(Queue * queue, void * hash, void * ptr);
void * queue_weed(Queue * queue);
void * queue_peek(Queue * queue);
void queue_insert(Queue * queue, void * hash, void * ptr);
void queue_toFront(Queue * queue, Node node);

jclass getMethodDeclaringClass(JNIEnv * env, jobject method);
jclass getMethodReturnType(JNIEnv * env, jobject method);
jclass getFieldDeclaringClass(JNIEnv * env, jobject method);
jclass getFieldType(JNIEnv * env, jobject method);
jclass getConstructorDeclaringClass(JNIEnv * env, jobject constructor);

jobject wrapInt(JNIEnv * env, jint value);
jint unwrapInt(JNIEnv * env, jobject value);

jobject wrapShort(JNIEnv * env, jshort value);
jshort unwrapShort(JNIEnv * env, jobject value);

jobject wrapFloat(JNIEnv * env, jfloat value);
jfloat unwrapFloat(JNIEnv * env, jobject value);

jobject wrapLong(JNIEnv * env, jlong value);
jlong unwrapLong(JNIEnv * env, jobject value);

jobject wrapByte(JNIEnv * env, jbyte value);
jbyte unwrapByte(JNIEnv * env, jobject value);

jobject wrapChar(JNIEnv * env, jchar value);
jchar unwrapChar(JNIEnv * env, jobject value);

jobject wrapDouble(JNIEnv * env, jdouble value);
jdouble unwrapDouble(JNIEnv * env, jobject value);

jobject wrapBoolean(JNIEnv * env, jboolean value);
jboolean unwrapBoolean(JNIEnv * env, jobject value);

#endif //__CREFLECTION_UTIL_INC__
