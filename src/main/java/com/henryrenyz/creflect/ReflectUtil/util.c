//
// Created by HenryRenYz on 2021/2/26.
//

#include <stdlib.h>
#include "util.h"

jobject     LOCK = NULL;
jboolean    initialized = FALSE;

__GLOBAL__  jclass      Method = NULL;
__GLOBAL__  jclass      Field = NULL;
__GLOBAL__  jclass      Constructor;

jfieldID    Method_parameterTypes = NULL;
jfieldID    Method_returnType = NULL;
jfieldID    Method_clazz = NULL;
jfieldID    Method_modifiers = NULL;
jfieldID    Field_type = NULL;
jfieldID    Field_clazz = NULL;
jfieldID    Field_modifiers = NULL;
jfieldID    Constructor_clazz = NULL;
jfieldID    Constructor_parameterTypes = NULL;

__GLOBAL__  jclass      Class = NULL;
__GLOBAL__  jclass      Object = NULL;
jmethodID   Object_toString = NULL;
jmethodID   Object_hashCode = NULL;

__GLOBAL__  jclass      Integer = NULL;
jint        Integer_hash;
jint        __int_hash__;
__GLOBAL__  jclass      __int__ = NULL;
jfieldID    Integer_value = NULL;
jmethodID   Integer_valueOf = NULL;

__GLOBAL__  jclass      Short = NULL;
jint        Short_hash;
jint        __short_hash__;
__GLOBAL__  jclass      __short__ = NULL;
jfieldID    Short_value = NULL;
jmethodID   Short_valueOf = NULL;

__GLOBAL__  jclass      Long = NULL;
jint        Long_hash;
jint        __long_hash__;
__GLOBAL__  jclass      __long__ = NULL;
jfieldID    Long_value = NULL;
jmethodID   Long_valueOf = NULL;

__GLOBAL__  jclass      Byte = NULL;
jint        Byte_hash;
jint        __byte_hash__;
__GLOBAL__  jclass      __byte__ = NULL;
jfieldID    Byte_value = NULL;
jmethodID   Byte_valueOf = NULL;

__GLOBAL__  jclass      Float = NULL;
jint        Float_hash;
jint        __float_hash__;
__GLOBAL__  jclass      __float__ = NULL;
jfieldID    Float_value = NULL;
jmethodID   Float_valueOf = NULL;

__GLOBAL__  jclass      Double = NULL;
jint        Double_hash;
jint        __double_hash__;
__GLOBAL__  jclass      __double__ = NULL;
jfieldID    Double_value = NULL;
jmethodID   Double_valueOf = NULL;

__GLOBAL__  jclass      Character = NULL;
jint        Character_hash;
jint        __char_hash__;
__GLOBAL__  jclass      __char__ = NULL;
jfieldID    Character_value = NULL;
jmethodID   Character_valueOf = NULL;

__GLOBAL__  jclass      Boolean = NULL;
jint        Boolean_hash;
jint        __boolean_hash__;
__GLOBAL__  jclass      __boolean__ = NULL;
jfieldID    Boolean_value = NULL;
jmethodID   Boolean_valueOf = NULL;

__GLOBAL__  jclass      Void = NULL;
jint        Void_hash;
jint        __void_hash__;
__GLOBAL__  jclass      __void__ = NULL;

__GLOBAL__  jclass      RuntimeException = NULL;
__GLOBAL__  jclass      IllegalArgumentException;
__GLOBAL__  jclass      NullPointerException = NULL;
jmethodID   newRuntimeException = NULL;



jboolean INIT(JNIEnv * env) {
    if (initialized) return TRUE;

    // Class.class
    Class = GLOBAL_REF_CLASS(java/lang/Class);
    Object = GLOBAL_REF_CLASS(java/lang/Object);
    Object_hashCode = ENV GetMethodID(env, Object, "hashCode", "()I");
    Object_toString = ENV GetMethodID(env, Object, "toString", "()Ljava/lang/String;");
    LOCK = GLOBAL_REF(ENV AllocObject(env, Object));
    if (Class == NULL || Object == NULL || Object_hashCode == NULL) return FALSE;

    // Integer.class & int.class
    Integer = GLOBAL_REF_CLASS(java/lang/Integer);
    __int__ = GLOBAL_REF(GET_STATIC_FIELD_OBJ(Integer, STATIC_FIELD_ID(Integer, "TYPE", "Ljava/lang/Class;")));
    if (__int__ == NULL) return FALSE;
    Integer_hash = ENV CallIntMethod(env, Integer, Object_hashCode);
    __int_hash__ = ENV CallIntMethod(env, __int__, Object_hashCode);
    Integer_valueOf = ENV GetStaticMethodID(env, Integer, "valueOf", "(I)Ljava/lang/Integer;");
    Integer_value = ENV GetFieldID(env, Integer, "value", "I");

    // Short.class & short.class
    Short = GLOBAL_REF_CLASS(java/lang/Short);
    __short__ = GLOBAL_REF(GET_STATIC_FIELD_OBJ(Short, STATIC_FIELD_ID(Short, "TYPE", "Ljava/lang/Class;")));
    if (__short__ == NULL) return FALSE;
    Short_hash = ENV CallIntMethod(env, Short, Object_hashCode);
    __short_hash__ = ENV CallIntMethod(env, __short__, Object_hashCode);
    Short_valueOf = ENV GetStaticMethodID(env, Short, "valueOf", "(S)Ljava/lang/Short;");
    Short_value = ENV GetFieldID(env, Short, "value", "S");

    // Long.class & long.class
    Long = GLOBAL_REF_CLASS(java/lang/Long);
    __long__ = GLOBAL_REF(GET_STATIC_FIELD_OBJ(Long, STATIC_FIELD_ID(Long, "TYPE", "Ljava/lang/Class;")));
    if (__long__ == NULL) return FALSE;
    Long_hash = ENV CallIntMethod(env, Long, Object_hashCode);
    __long_hash__ = ENV CallIntMethod(env, __long__, Object_hashCode);
    Long_valueOf = ENV GetStaticMethodID(env, Long, "valueOf", "(J)Ljava/lang/Long;");
    Long_value = ENV GetFieldID(env, Long, "value", "J");

    // Byte.class & byte.class
    Byte = GLOBAL_REF_CLASS(java/lang/Byte);
    __byte__ = GLOBAL_REF(GET_STATIC_FIELD_OBJ(Byte, STATIC_FIELD_ID(Byte, "TYPE", "Ljava/lang/Class;")));
    if (__byte__ == NULL) return FALSE;
    Byte_hash = ENV CallIntMethod(env, Byte, Object_hashCode);
    __byte_hash__ = ENV CallIntMethod(env, __byte__, Object_hashCode);
    Byte_valueOf = ENV GetStaticMethodID(env, Byte, "valueOf", "(B)Ljava/lang/Byte;");
    Byte_value = ENV GetFieldID(env, Byte, "value", "B");

    // Float.class & float.class
    Float = GLOBAL_REF_CLASS(java/lang/Float);
    __float__ = GLOBAL_REF(GET_STATIC_FIELD_OBJ(Float, STATIC_FIELD_ID(Float, "TYPE", "Ljava/lang/Class;")));
    if (__float__ == NULL) return FALSE;
    Float_hash = ENV CallIntMethod(env, Float, Object_hashCode);
    __float_hash__ = ENV CallIntMethod(env, __float__, Object_hashCode);
    Float_valueOf = ENV GetStaticMethodID(env, Float, "valueOf", "(F)Ljava/lang/Float;");
    Float_value = ENV GetFieldID(env, Float, "value", "F");

    // Double.class & double.class
    Double = GLOBAL_REF_CLASS(java/lang/Double);
    __double__ = GLOBAL_REF(GET_STATIC_FIELD_OBJ(Double, STATIC_FIELD_ID(Double, "TYPE", "Ljava/lang/Class;")));
    if (__double__ == NULL) return FALSE;
    Double_hash = ENV CallIntMethod(env, Double, Object_hashCode);
    __double_hash__ = ENV CallIntMethod(env, __double__, Object_hashCode);
    Double_valueOf = ENV GetStaticMethodID(env, Double, "valueOf", "(D)Ljava/lang/Double;");
    Double_value = ENV GetFieldID(env, Double, "value", "D");

    // Character.class & char.class
    Character = GLOBAL_REF_CLASS(java/lang/Character);
    __char__ = GLOBAL_REF(GET_STATIC_FIELD_OBJ(Character, STATIC_FIELD_ID(Character, "TYPE", "Ljava/lang/Class;")));
    if (__char__ == NULL) return FALSE;
    Character_hash = ENV CallIntMethod(env, Character, Object_hashCode);
    __char_hash__ = ENV CallIntMethod(env, __char__, Object_hashCode);
    Character_valueOf = ENV GetStaticMethodID(env, Character, "valueOf", "(C)Ljava/lang/Character;");
    Character_value = ENV GetFieldID(env, Character, "value", "C");

    // Boolean.class & boolean.class
    Boolean = GLOBAL_REF_CLASS(java/lang/Boolean);
    __boolean__ = GLOBAL_REF(GET_STATIC_FIELD_OBJ(Boolean, STATIC_FIELD_ID(Boolean, "TYPE", "Ljava/lang/Class;")));
    if (__boolean__ == NULL) return FALSE;
    Boolean_hash = ENV CallIntMethod(env, Boolean, Object_hashCode);
    __boolean_hash__ = ENV CallIntMethod(env, __boolean__, Object_hashCode);
    Boolean_valueOf = ENV GetStaticMethodID(env, Boolean, "valueOf", "(Z)Ljava/lang/Boolean;");
    Boolean_value = FIELD_ID(Boolean, "value", "Z");

    // Void.class & void.class
    Void = GLOBAL_REF_CLASS(java/lang/Void);
    __void__ = GLOBAL_REF(GET_STATIC_FIELD_OBJ(Void, STATIC_FIELD_ID(Void, "TYPE", "Ljava/lang/Class;")));
    if (__void__ == NULL) return FALSE;
    Void_hash = ENV CallIntMethod(env, Void, Object_hashCode);
    __void_hash__ = ENV CallIntMethod(env, __void__, Object_hashCode);

    // Method.class & Field.class
    Method = GLOBAL_REF_CLASS(java/lang/reflect/Method);
    Field = GLOBAL_REF_CLASS(java/lang/reflect/Field);
    Constructor = GLOBAL_REF_CLASS(java/lang/reflect/Constructor);
    if (Method == NULL || Field == NULL) return FALSE;

    Method_parameterTypes = FIELD_ID(Method, "parameterTypes", "[Ljava/lang/Class;");
    // returnType field for Method.class
    Method_returnType = FIELD_ID(Method, "returnType", "Ljava/lang/Class;");
    // related class of a method
    Method_clazz = FIELD_ID(Method, "clazz", "Ljava/lang/Class;");

    Method_modifiers = FIELD_ID(Method, "modifiers",  "I");

    Field_type = FIELD_ID(Field, "type", "Ljava/lang/Class;");

    Field_clazz = FIELD_ID(Field, "clazz", "Ljava/lang/Class;");

    Field_modifiers = FIELD_ID(Field, "modifiers", "I");

    Constructor_clazz = FIELD_ID(Constructor, "clazz", "Ljava/lang/Class;");

    Constructor_parameterTypes = FIELD_ID(Constructor, "parameterTypes", "[Ljava/lang/Class;");

    // InvocationTargetException.class to wrap exception
    RuntimeException = GLOBAL_REF_CLASS(java/lang/RuntimeException);
    newRuntimeException = ENV GetMethodID(env, RuntimeException, "<init>", "(Ljava/lang/String;Ljava/lang/Throwable;)V");
    NullPointerException = GLOBAL_REF_CLASS(java/lang/NullPointerException);
    IllegalArgumentException = GLOBAL_REF_CLASS(java/lang/IllegalArgumentException);

    // Initialized marker
    initialized = TRUE;

    return !(Integer_value == NULL || Short_value == NULL || Long_value == NULL || Byte_value == NULL
             || Float_value == NULL || Double_value == NULL || Character_value == NULL || Boolean_value == NULL
             || Method_parameterTypes == NULL || Method_returnType == NULL);

}


// add to last
void queue_add(Queue * queue, void * hash, void * ptr) {
    Node new = malloc(sizeof(struct Node));
    new->next = NULL;
    new->key = hash;
    new->value = ptr;
    if (queue->size == 0) {
        queue->start = new;
        queue->end = new;
        new->prev = NULL;
    } else {
        queue->end->next = new;
        new->prev = queue->end;
        queue->end = new;
    }
    ++queue->size;
}

// remove last
void * queue_weed(Queue * queue) {
    if (queue->size == 0) return NULL;
    Node last = queue->end;
    void * ptr = last->value;
    if (queue->size == 1) {
        queue->start = NULL;
        queue->end = NULL;
    } else {
        queue->end = queue->end->prev;
    }
    --queue->size;
    free(last);
    return ptr;
}

// get the first element
inline void * queue_peek(Queue * queue) {
    return queue->start;
}

// insert to front
void queue_insert(Queue * queue, void * hash, void * ptr) {
    Node new = malloc(sizeof(struct Node));
    new->prev = NULL;
    new->key = hash;
    new->value = ptr;
    if (queue->size == 0) {
        queue->start = new;
        queue->end = new;
        new->next = NULL;
    } else {
        new->next = queue->start;
        queue->start->prev = new;
        queue->start = new;
    }
    ++queue->size;
}

void queue_toFront(Queue * queue, Node node) {
    if (queue->size == 2) {
        node->next = node->prev;
        node->prev->prev = node;
        node->prev->next = NULL;
        node->prev = NULL;
        queue->start = node;
        queue->end = node->next;
    } else {
        if (node == queue->end) {
            queue->end = node->prev;
            queue->end->next = NULL;
            node->next = queue->start;
            node->prev = NULL;
            queue->start->prev = node;
            queue->start = node;
        } else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
            node->next = queue->start;
            node->prev = NULL;
            queue->start->prev = node;
            queue->start = node;
        }
    }
}


inline jclass getMethodDeclaringClass(JNIEnv * env, jobject method) {
    return GET_FIELD_OBJ(method, Method_clazz);
}

inline jclass getMethodReturnType(JNIEnv * env, jobject method) {
    return GET_FIELD_OBJ(method, Method_returnType);
}

inline jclass getFieldDeclaringClass(JNIEnv * env, jobject method) {
    return GET_FIELD_OBJ(method, Field_clazz);
}

inline jclass getFieldType(JNIEnv * env, jobject method) {
    return GET_FIELD_OBJ(method, Field_type);
}

inline jclass getConstructorDeclaringClass(JNIEnv * env, jobject constructor) {
    return GET_FIELD_OBJ(constructor, Constructor_clazz);
}

inline jobject wrapInt(JNIEnv * env, jint value) {
    return ENV CallStaticObjectMethod(env, Integer, Integer_valueOf, value);
}

inline jint unwrapInt(JNIEnv * env, jobject value) {
    return ENV GetIntField(env, value, Integer_value);
}

inline jobject wrapShort(JNIEnv * env, jshort value) {
    return ENV CallStaticObjectMethod(env, Short, Short_valueOf, value);
}

inline jshort unwrapShort(JNIEnv * env, jobject value) {
    return ENV GetShortField(env, value, Short_value);
}

inline jobject wrapFloat(JNIEnv * env, jfloat value) {
    return ENV CallStaticObjectMethod(env, Float, Float_valueOf, value);
}

inline jfloat unwrapFloat(JNIEnv * env, jobject value) {
    return ENV GetFloatField(env, value, Float_value);
}

inline jobject wrapLong(JNIEnv * env, jlong value) {
    return ENV CallStaticObjectMethod(env, Long, Long_valueOf, value);
}

inline jlong unwrapLong(JNIEnv * env, jobject value) {
    return ENV GetLongField(env, value, Long_value);
}

inline jobject wrapByte(JNIEnv * env, jbyte value) {
    return ENV CallStaticObjectMethod(env, Byte, Byte_valueOf, value);
}

inline jbyte unwrapByte(JNIEnv * env, jobject value) {
    return ENV GetByteField(env, value, Byte_value);
}

inline jobject wrapChar(JNIEnv * env, jchar value) {
    return ENV CallStaticObjectMethod(env, Character, Character_valueOf, value);
}

inline jchar unwrapChar(JNIEnv * env, jobject value) {
    return ENV GetCharField(env, value, Character_value);
}

inline jobject wrapDouble(JNIEnv * env, jdouble value) {
    return ENV CallStaticObjectMethod(env, Double, Double_valueOf, value);
}

inline jdouble unwrapDouble(JNIEnv * env, jobject value) {
    return ENV GetDoubleField(env, value, Double_value);
}

inline jobject wrapBoolean(JNIEnv * env, jboolean value) {
    return ENV CallStaticObjectMethod(env, Boolean, Boolean_valueOf, value);
}

inline jboolean unwrapBoolean(JNIEnv * env, jobject value) {
    return ENV GetBooleanField(env, value, Boolean_value);
}

