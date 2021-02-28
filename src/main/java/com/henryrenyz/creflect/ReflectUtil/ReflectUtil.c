//
// Created by HenryRenYz on 2021/2/25.
//
//
// Created by HenryRenYz on 2021/2/25.
//

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "util.h"
#include "com_henryrenyz_creflect_ReflectLibImpl.h"

static const int MAX_CACHE = 64;







/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    refUtilInit0
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_refUtilInit0
(JNIEnv * env, jclass cls) {
    if (!initialized) return INIT(env);
    return TRUE;
}







jvalue * formValueList(JNIEnv * env, jobjectArray paramerTypes, jobjectArray params) {

    jsize size = LENGTH_OF(params);
    if (size != LENGTH_OF(paramerTypes)) {
        ENV ThrowNew(env, IllegalArgumentException, "Invalid arguments!");
        return NULL;
    }

    jvalue * jvargs = malloc(sizeof(union jvalue) * size);
    jint hash;

    for (register int i = 0; i < size; i++) {

        hash = ENV CallIntMethod(env, ELE_OF(paramerTypes, i), Object_hashCode);

        if      (hash == __int_hash__)
            jvargs[i] = (jvalue) unwrapInt(env, ELE_OF(params, i));
        else if (hash == __short_hash__)
            jvargs[i] = (jvalue) unwrapShort(env, ELE_OF(params, i));
        else if (hash == __long_hash__)
            jvargs[i] = (jvalue) unwrapLong(env, ELE_OF(params, i));
        else if (hash == __char_hash__)
            jvargs[i] = (jvalue) unwrapChar(env, ELE_OF(params, i));
        else if (hash == __byte_hash__)
            jvargs[i] = (jvalue) unwrapByte(env, ELE_OF(params, i));
        else if (hash == __float_hash__)
            jvargs[i] = (jvalue) unwrapFloat(env, ELE_OF(params, i));
        else if (hash == __double_hash__)
            jvargs[i] = (jvalue) unwrapDouble(env, ELE_OF(params, i));
        else if (hash == __boolean_hash__)
            jvargs[i] = (jvalue) unwrapBoolean(env, ELE_OF(params, i));
        else
            jvargs[i] = (jvalue) ELE_OF(params, i);
    }
    return jvargs;
}

static void throwInvocationTargetException(JNIEnv * env, jthrowable throwable) {
    ENV ExceptionClear(env);
    jstring str = ENV NewStringUTF(env, "An exception occurred while reflecting a method!");
    jthrowable new = ENV NewObject(env, RuntimeException, newRuntimeException, str, throwable);
    ENV Throw(env, new);
}

//static Queue MethodCache = {NULL, NULL};

//TODO: Fix this shit!
/*static jmethodID getMethodId(JNIEnv * env, jobject mth) {
    return ENV FromReflectedMethod(env, mth);
    Node node = MethodCache.start;
    while (node != NULL) {
        if (node->key == mth) {
            // teleport to front
            if (node != MethodCache.start) {
                synchronized (LOCK) {
                    queue_toFront(&MethodCache, node);
                }
            }
            return (jmethodID) node->value;
        }
        node = node->next;
    }
    jmethodID id = ENV FromReflectedMethod(env, mth);
    synchronized (LOCK) {
        queue_insert(&MethodCache, mth, id);
        if (MethodCache.size > MAX_CACHE) queue_weed(&MethodCache);
    }
    return id;
}*/

void throwInvalidInstance(JNIEnv * env, jobject member, jclass expectedClass) {
    char msg[256] = {0};
    const char * temp = NULL;
    jstring str = NULL;

    strcat(msg, "Object (");

    str = ENV CallObjectMethod(env, GET_CLASS(member), Object_toString);
    temp = ENV GetStringUTFChars(env, str, NULL);
    strcat(msg, temp);
    ENV ReleaseStringUTFChars(env, str, temp);

    strcat(msg, ") is not a member of ");

    str = ENV CallObjectMethod(env, expectedClass, Object_toString);
    temp = ENV GetStringUTFChars(env, str, NULL);
    strcat(msg, temp);
    ENV ReleaseStringUTFChars(env, str, temp);

    ENV ThrowNew(env, IllegalArgumentException, msg);
}

static jboolean checkMethodStaticValidation(JNIEnv * env, jobject mth, jobject member) {
    jboolean isStatic = (ENV GetIntField(env, mth, Method_modifiers) & MODIFIER_STATIC) != 0;
    if (!isStatic && member == NULL) {
        ENV ThrowNew(env, NullPointerException, "Invocation of null member for non-static method");
    }
    return isStatic;
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    callMethodObject0
 * Signature: (Ljava/lang/reflect/Method;Ljava/lang/Object;[Ljava/lang/Object;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_callMethodObject0
(JNIEnv * env, jclass cls, jobject mth, jobject member, jobjectArray params) {

    jvalue * value = formValueList(env, ENV GetObjectField(env, mth, Method_parameterTypes), params);

    jmethodID id = ENV FromReflectedMethod(env, mth);

    jint hash = ENV CallIntMethod(env, getMethodReturnType(env, mth), Object_hashCode);
    jclass mth_class = getMethodDeclaringClass(env, mth);

    jobject returns = NULL;
    jboolean isStatic = checkMethodStaticValidation(env, mth, member);
    if (ENV ExceptionCheck(env)) return NULL;

    returns = ENV CallObjectMethod(env, member, id);

    if (isStatic) {
        if      (hash == __int_hash__)
            returns = wrapInt(env, ENV CallStaticIntMethodA(env, mth_class, id, value));
        else if (hash == __short_hash__)
            returns = wrapShort(env, ENV CallStaticShortMethodA(env, mth_class, id, value));
        else if (hash == __byte_hash__)
            returns = wrapByte(env, ENV CallStaticByteMethodA(env, mth_class, id, value));
        else if (hash == __char_hash__)
            returns = wrapChar(env, ENV CallStaticCharMethodA(env, mth_class, id, value));
        else if (hash == __long_hash__)
            returns = wrapLong(env, ENV CallStaticLongMethodA(env, mth_class, id, value));
        else if (hash == __float_hash__)
            returns = wrapFloat(env, ENV CallStaticFloatMethodA(env, mth_class, id, value));
        else if (hash == __double_hash__)
            returns = wrapDouble(env, ENV CallStaticDoubleMethodA(env, mth_class, id, value));
        else if (hash == __boolean_hash__)
            returns = wrapBoolean(env, ENV CallStaticBooleanMethodA(env, mth_class, id, value));
        else if (hash == __void_hash__)
            ENV CallStaticVoidMethodA(env, mth_class, id, value);
        else
            returns = ENV CallStaticObjectMethodA(env, mth_class, id, value);
    } else {
        if (!ENV IsInstanceOf(env, member, mth_class)) {
            throwInvalidInstance(env, member, mth_class);
            return NULL;
        }
        if      (hash == __int_hash__)
            returns = wrapInt(env, ENV CallIntMethodA(env, member, id, value));
        else if (hash == __short_hash__)
            returns = wrapShort(env, ENV CallShortMethodA(env, member, id, value));
        else if (hash == __byte_hash__)
            returns = wrapByte(env, ENV CallByteMethodA(env, member, id, value));
        else if (hash == __char_hash__)
            returns = wrapChar(env, ENV CallCharMethodA(env, member, id, value));
        else if (hash == __long_hash__)
            returns = wrapLong(env, ENV CallLongMethodA(env, member, id, value));
        else if (hash == __float_hash__)
            returns = wrapFloat(env, ENV CallFloatMethodA(env, member, id, value));
        else if (hash == __double_hash__)
            returns = wrapDouble(env, ENV CallDoubleMethodA(env, member, id, value));
        else if (hash == __boolean_hash__)
            returns = wrapBoolean(env, ENV CallBooleanMethodA(env, member, id, value));
        else if (hash == __void_hash__)
            ENV CallVoidMethodA(env, member, id, value);
        else
            returns = ENV CallObjectMethodA(env, member, id, value);
    }

    free(value);
    ENV DeleteLocalRef(env, mth_class);

    //if Exception exists
    if (ENV ExceptionCheck(env)) {
        jthrowable t = ENV ExceptionOccurred(env);
        throwInvocationTargetException(env, t);
        return NULL;
    }

    /*printf("Value Address: %p\n", returns);
    jclass ccls = GET_CLASS(returns);
    jstring clsname = ENV CallObjectMethod(env, ccls, Object_toString);
    const char * name = ENV GetStringUTFChars(env, clsname, NULL);
    printf("Value class: %s\n", name);
    ENV ReleaseStringUTFChars(env, clsname, name);*/
    return returns;
}

#define CALL_METHOD_PRIMITIVE(_type, _typeCapital)                                                      \
    jvalue * value = formValueList(env, ENV GetObjectField(env, mth, Method_parameterTypes), params);   \
    jmethodID id = ENV FromReflectedMethod(env, mth);                                                   \
    jclass mth_class = getMethodDeclaringClass(env, mth);                                               \
    j##_type returns = 0;                                                                               \
    jboolean isStatic = checkMethodStaticValidation(env, mth, member);                                  \
    if (ENV ExceptionCheck(env)) return 0;                                                              \
    if (isStatic) {                                                                                     \
        returns = ENV CallStatic##_typeCapital##MethodA(env, mth_class, id, value);                     \
    } else {                                                                                            \
        if (!ENV IsInstanceOf(env, member, mth_class)) {                                                \
            throwInvalidInstance(env, member, mth_class);                                               \
            return 0;                                                                                   \
        }                                                                                               \
        returns = ENV Call##_typeCapital##MethodA(env, member, id, value);                              \
    }                                                                                                   \
    free(value);                                                                                        \
    if (ENV ExceptionCheck(env)) {                                                                      \
        jthrowable t = ENV ExceptionOccurred(env);                                                      \
        throwInvocationTargetException(env, t);                                                         \
        return 0;                                                                                       \
    }                                                                                                   \
    return returns;


/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    callMethodInt0
 * Signature: (Ljava/lang/reflect/Method;Ljava/lang/Object;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_callMethodInt0
(JNIEnv * env, jclass cls, jobject mth, jobject member, jobjectArray params) {
    CALL_METHOD_PRIMITIVE(int, Int);
}
/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    callMethodShort0
 * Signature: (Ljava/lang/reflect/Method;Ljava/lang/Object;[Ljava/lang/Object;)S
 */
JNIEXPORT jshort JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_callMethodShort0
(JNIEnv * env, jclass cls, jobject mth, jobject member, jobjectArray params) {
    CALL_METHOD_PRIMITIVE(short, Short);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    callMethodByte0
 * Signature: (Ljava/lang/reflect/Method;Ljava/lang/Object;[Ljava/lang/Object;)B
 */
JNIEXPORT jbyte JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_callMethodByte0
(JNIEnv * env, jclass cls, jobject mth, jobject member, jobjectArray params) {
    CALL_METHOD_PRIMITIVE(byte, Byte);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    callMethodLong0
 * Signature: (Ljava/lang/reflect/Method;Ljava/lang/Object;[Ljava/lang/Object;)J
 */
JNIEXPORT jlong JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_callMethodLong0
(JNIEnv * env, jclass cls, jobject mth, jobject member, jobjectArray params) {
    CALL_METHOD_PRIMITIVE(long, Long);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    callMethodFloat0
 * Signature: (Ljava/lang/reflect/Method;Ljava/lang/Object;[Ljava/lang/Object;)F
 */
JNIEXPORT jfloat JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_callMethodFloat0
(JNIEnv * env, jclass cls, jobject mth, jobject member, jobjectArray params) {
    CALL_METHOD_PRIMITIVE(float, Float);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    callMethodDouble0
 * Signature: (Ljava/lang/reflect/Method;Ljava/lang/Object;[Ljava/lang/Object;)D
 */
JNIEXPORT jdouble JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_callMethodDouble0
(JNIEnv * env, jclass cls, jobject mth, jobject member, jobjectArray params) {
    CALL_METHOD_PRIMITIVE(double, Double);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    callMethodBoolean0
 * Signature: (Ljava/lang/reflect/Method;Ljava/lang/Object;[Ljava/lang/Object;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_callMethodBoolean0
(JNIEnv * env, jclass cls, jobject mth, jobject member, jobjectArray params) {
    CALL_METHOD_PRIMITIVE(boolean, Boolean);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    callMethodChar0
 * Signature: (Ljava/lang/reflect/Method;Ljava/lang/Object;[Ljava/lang/Object;)C
 */
JNIEXPORT jchar JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_callMethodChar0
(JNIEnv * env, jclass cls, jobject mth, jobject member, jobjectArray params) {
    CALL_METHOD_PRIMITIVE(char, Char);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    callMethodVoid0
 * Signature: (Ljava/lang/reflect/Method;Ljava/lang/Object;[Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_callMethodVoid0
(JNIEnv * env, jclass cls, jobject mth, jobject member, jobjectArray params) {

    jvalue *value = formValueList(env, ENV GetObjectField(env, mth, Method_parameterTypes), params);

    jmethodID id = ENV FromReflectedMethod(env, mth);
    jclass mth_class = getMethodDeclaringClass(env, mth);

    jboolean isStatic = checkMethodStaticValidation(env, mth, member);
    if (ENV ExceptionCheck(env)) return;

    if (isStatic) {
        ENV CallStaticVoidMethodA(env, mth_class, id, value);
    }
    else {
        if (!ENV IsInstanceOf(env, member, mth_class)) {
            throwInvalidInstance(env, member, mth_class);
            return;
        }
        ENV CallVoidMethodA(env, member, id, value);
    }

    free(value);

    if (ENV ExceptionCheck(env)) {
        jthrowable t = ENV ExceptionOccurred(env);
        throwInvocationTargetException(env, t);
        return;
    }
}









//static Queue FieldCache = {NULL, NULL};

//TODO: Fix this shit
/*static jfieldID getFieldId(JNIEnv * env, jobject field) {
    return ENV FromReflectedField(env, field);
    Node node = FieldCache.start;
    while (node != NULL) {
        if (node->key == field) {
            // teleport to front
            if (node != FieldCache.start) {
                synchronized (LOCK) {
                    queue_toFront(&FieldCache, node);
                }
            }
            return (jfieldID) node->value;
        }
        node = node->next;
    }
    jfieldID id = ENV FromReflectedField(env, field);
    synchronized (LOCK) {
        queue_insert(&FieldCache, field, id);
        if (FieldCache.size > MAX_CACHE) queue_weed(&FieldCache);
    }
    return id;
}*/

static jboolean checkFieldStaticValidation(JNIEnv * env, jobject field, jobject member) {
    jboolean isStatic = (ENV GetIntField(env, field, Field_modifiers) & MODIFIER_STATIC) != 0;
    if (!isStatic && member == NULL) {
        ENV ThrowNew(env, NullPointerException, "Invocation of null member for non-static method");
    }
    return isStatic;
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    getFieldObject0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_getFieldObject0
(JNIEnv * env, jclass cls, jobject field, jobject member) {

    jfieldID id = ENV FromReflectedField(env, field);

    jint hash = ENV CallIntMethod(env, getFieldType(env, field), Object_hashCode);
    jclass field_class = getFieldDeclaringClass(env, field);

    jboolean isStatic = checkFieldStaticValidation(env, field, member);
    if (ENV ExceptionCheck(env)) return NULL;

    jobject returns = NULL;
    if (isStatic) {
        if      (hash == __int_hash__)
            returns = wrapInt(env, ENV GetStaticIntField(env, field_class, id));
        else if (hash == __short_hash__)
            returns = wrapShort(env, ENV GetStaticShortField(env, field_class, id));
        else if (hash == __byte_hash__)
            returns = wrapByte(env, ENV GetStaticByteField(env, field_class, id));
        else if (hash == __char_hash__)
            returns = wrapChar(env, ENV GetStaticCharField(env, field_class, id));
        else if (hash == __long_hash__)
            returns = wrapLong(env, ENV GetStaticLongField(env, field_class, id));
        else if (hash == __float_hash__)
            returns = wrapFloat(env, ENV GetStaticFloatField(env, field_class, id));
        else if (hash == __double_hash__)
            returns = wrapDouble(env, ENV GetStaticDoubleField(env, field_class, id));
        else if (hash == __boolean_hash__)
            returns = wrapBoolean(env, ENV GetStaticBooleanField(env, field_class, id));
        else
            returns = ENV GetStaticObjectField(env, field_class, id);
    } else {
        if (!ENV IsInstanceOf(env, member, field_class)) {
            throwInvalidInstance(env, member, field_class);
            return NULL;
        }
        if      (hash == __int_hash__)
            returns = wrapInt(env, ENV GetIntField(env, member, id));
        else if (hash == __short_hash__)
            returns = wrapShort(env, ENV GetShortField(env, member, id));
        else if (hash == __byte_hash__)
            returns = wrapByte(env, ENV GetByteField(env, member, id));
        else if (hash == __char_hash__)
            returns = wrapChar(env, ENV GetCharField(env, member, id));
        else if (hash == __long_hash__)
            returns = wrapLong(env, ENV GetLongField(env, member, id));
        else if (hash == __float_hash__)
            returns = wrapFloat(env, ENV GetFloatField(env, member, id));
        else if (hash == __double_hash__)
            returns = wrapDouble(env, ENV GetDoubleField(env, member, id));
        else if (hash == __boolean_hash__)
            returns = wrapBoolean(env, ENV GetBooleanField(env, member, id));
        else
            returns = ENV GetObjectField(env, member, id);
    }

    return returns;
}


#define GET_FIELD_PRIMITIVE(_type, _typeCapital)                                    \
    jfieldID id = ENV FromReflectedField(env, field);                               \
    jclass field_class = getFieldDeclaringClass(env, field);                        \
    j##_type returns = 0;                                                           \
    jboolean isStatic = checkFieldStaticValidation(env, field, member);             \
    if (ENV ExceptionCheck(env)) return 0;                                          \
    if (isStatic) {                                                                 \
        returns = ENV GetStatic##_typeCapital##Field(env, field_class, id);         \
    } else {                                                                        \
        if (!ENV IsInstanceOf(env, member, field_class)) {                          \
            throwInvalidInstance(env, member, field_class);                         \
            return 0;                                                               \
        }                                                                           \
            returns = ENV Get##_typeCapital##Field(env, member, id);                \
    }                                                                               \
    return returns;

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    getFieldInt0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_getFieldInt0
(JNIEnv * env, jclass cls, jobject field, jobject member) {
    GET_FIELD_PRIMITIVE(int, Int);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    getFieldShort0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;)S
 */
JNIEXPORT jshort JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_getFieldShort0
(JNIEnv * env, jclass cls, jobject field, jobject member) {
    GET_FIELD_PRIMITIVE(short, Short);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    getFieldByte0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;)B
 */
JNIEXPORT jbyte JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_getFieldByte0
(JNIEnv * env, jclass cls, jobject field, jobject member) {
    GET_FIELD_PRIMITIVE(byte, Byte);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    getFieldLong0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;)J
 */
JNIEXPORT jlong JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_getFieldLong0
(JNIEnv * env, jclass cls, jobject field, jobject member) {
    GET_FIELD_PRIMITIVE(long, Long);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    getFieldFloat0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;)F
 */
JNIEXPORT jfloat JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_getFieldFloat0
(JNIEnv * env, jclass cls, jobject field, jobject member) {
    GET_FIELD_PRIMITIVE(float, Float);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    getFieldDouble0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;)D
 */
JNIEXPORT jdouble JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_getFieldDouble0
(JNIEnv * env, jclass cls, jobject field, jobject member) {
    GET_FIELD_PRIMITIVE(double, Double);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    getFieldBoolean0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_getFieldBoolean0
(JNIEnv * env, jclass cls, jobject field, jobject member) {
    GET_FIELD_PRIMITIVE(boolean, Boolean);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    getFieldChar0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;)C
 */
JNIEXPORT jchar JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_getFieldChar0
(JNIEnv * env, jclass cls, jobject field, jobject member) {
    GET_FIELD_PRIMITIVE(char, Char);
}









/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    setFieldObject0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_setFieldObject0
(JNIEnv * env, jclass cls, jobject field, jobject member, jobject value) {
    jfieldID id = ENV FromReflectedField(env, field);

    jint hash = ENV CallIntMethod(env, getFieldType(env, field), Object_hashCode);
    jint value_hash = ENV CallIntMethod(env, GET_CLASS(value), Object_hashCode);
    jclass field_class = getFieldDeclaringClass(env, field);

    jboolean isStatic = checkFieldStaticValidation(env, field, member);
    if (ENV ExceptionCheck(env)) return;

    if (isStatic) {
        if      (hash == __int_hash__) {
            if (value_hash == Integer_hash) {
                ENV SetStaticIntField(env, field_class, id, unwrapInt(env, value));
                return;
            }
        }
        else if (hash == __short_hash__) {
            if (value_hash == Short_hash) {
                ENV SetStaticShortField(env, field_class, id, unwrapShort(env, value));
                return;
            }
        }
        else if (hash == __byte_hash__) {
            if (value_hash == Byte_hash) {
                ENV SetStaticByteField(env, field_class, id, unwrapByte(env, value));
                return;
            }
        }
        else if (hash == __char_hash__) {
            if (value_hash == Character_hash) {
                ENV SetStaticCharField(env, field_class, id, unwrapChar(env, value));
                return;
            }
        }
        else if (hash == __long_hash__) {
            if (value_hash == Long_hash) {
                ENV SetStaticLongField(env, field_class, id, unwrapLong(env, value));
                return;
            }
        }
        else if (hash == __float_hash__) {
            if (value_hash == Float_hash) {
                ENV SetStaticFloatField(env, field_class, id, unwrapFloat(env, value));
                return;
            }
        }
        else if (hash == __double_hash__) {
            if (value_hash == Double_hash) {
                ENV SetStaticDoubleField(env, field_class, id, unwrapDouble(env, value));
                return;
            }
        }
        else if (hash == __boolean_hash__) {
            if (value_hash == Boolean_hash) {
                ENV SetStaticBooleanField(env, field_class, id, unwrapBoolean(env, value));
                return;
            }
        }
        else {
            ENV SetStaticObjectField(env, field_class, id, value);
            return;
        }
    } else {
        if (!ENV IsInstanceOf(env, member, field_class)) {
            throwInvalidInstance(env, member, field_class);
            return;
        }
        if      (hash == __int_hash__) {
            if (value_hash == Integer_hash) {
                ENV SetIntField(env, member, id, unwrapInt(env, value));
                return;
            }
        }
        else if (hash == __short_hash__) {
            if (value_hash == Short_hash) {
                ENV SetShortField(env, member, id, unwrapShort(env, value));
                return;
            }
        }
        else if (hash == __byte_hash__) {
            if (value_hash == Byte_hash) {
                ENV SetByteField(env, member, id, unwrapByte(env, value));
                return;
            }
        }
        else if (hash == __char_hash__) {
            if (value_hash == Character_hash) {
                ENV SetCharField(env, member, id, unwrapChar(env, value));
                return;
            }
        }
        else if (hash == __long_hash__) {
            if (value_hash == Long_hash) {
                ENV SetLongField(env, member, id, unwrapLong(env, value));
                return;
            }
        }
        else if (hash == __float_hash__) {
            if (value_hash == Float_hash) {
                ENV SetFloatField(env, member, id, unwrapFloat(env, value));
                return;
            }
        }
        else if (hash == __double_hash__) {
            if (value_hash == Double_hash) {
                ENV SetDoubleField(env, member, id, unwrapDouble(env, value));
                return;
            }
        }
        else if (hash == __boolean_hash__) {
            if (value_hash == Boolean_hash) {
                ENV SetBooleanField(env, member, id, unwrapBoolean(env, value));
                return;
            }
        }
        else {
            ENV SetObjectField(env, member, id, value);
            return;
        }
    }
    throwInvalidInstance(env, value, getFieldType(env, field));
}


#define SET_FIELD_PRIMITIVE(_typeCapital)                                       \
    jfieldID id = ENV FromReflectedField(env, field);                           \
    jclass field_class = getFieldDeclaringClass(env, field);                    \
    jboolean isStatic = checkFieldStaticValidation(env, field, member);         \
    if (ENV ExceptionCheck(env)) return;                                        \
    if (isStatic) {                                                             \
        ENV SetStatic##_typeCapital##Field(env, field_class, id, value);        \
    } else {                                                                    \
        if (!ENV IsInstanceOf(env, member, field_class)) {                      \
            throwInvalidInstance(env, member, field_class);                     \
            return;                                                             \
        }                                                                       \
        ENV Set##_typeCapital##Field(env, member, id, value);                   \
    }


/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    setFieldInt0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;I)V
 */
JNIEXPORT void JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_setFieldInt0
(JNIEnv * env, jclass cls, jobject field, jobject member, jint value) {
    SET_FIELD_PRIMITIVE(Int);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    setFieldShort0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;S)V
 */
JNIEXPORT void JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_setFieldShort0
(JNIEnv * env, jclass cls, jobject field, jobject member, jshort value) {
    SET_FIELD_PRIMITIVE(Short);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    setFieldByte0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;B)V
 */
JNIEXPORT void JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_setFieldByte0
(JNIEnv * env, jclass cls, jobject field, jobject member, jbyte value) {
    SET_FIELD_PRIMITIVE(Byte);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    setFieldLong0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;J)V
 */
JNIEXPORT void JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_setFieldLong0
(JNIEnv * env, jclass cls, jobject field, jobject member, jlong value) {
    SET_FIELD_PRIMITIVE(Long);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    setFieldFloat0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;F)V
 */
JNIEXPORT void JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_setFieldFloat0
(JNIEnv * env, jclass cls, jobject field, jobject member, jfloat value) {
    SET_FIELD_PRIMITIVE(Float);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    setFieldDouble0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;D)V
 */
JNIEXPORT void JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_setFieldDouble0
(JNIEnv * env, jclass cls, jobject field, jobject member, jdouble value) {
    SET_FIELD_PRIMITIVE(Double);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    setFieldBoolean0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;Z)V
 */
JNIEXPORT void JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_setFieldBoolean0
(JNIEnv * env, jclass cls, jobject field, jobject member, jboolean value) {
    SET_FIELD_PRIMITIVE(Boolean);
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    setFieldChar0
 * Signature: (Ljava/lang/reflect/Field;Ljava/lang/Object;C)V
 */
JNIEXPORT void JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_setFieldChar0
(JNIEnv * env, jclass cls, jobject field, jobject member, jchar value) {
    SET_FIELD_PRIMITIVE(Char);
}









/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    newInstance0
 * Signature: (Ljava/lang/reflect/Constructor;[Ljava/lang/Object;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_newInstance0
(JNIEnv * env, jclass cls, jobject constructor, jobjectArray params) {
    jvalue * value = formValueList(env,
                                   ENV GetObjectField(env,
                                                      constructor,
                                                      Constructor_parameterTypes),
                                   params);

    if (ENV ExceptionCheck(env)) return NULL;

    jobject result = ENV NewObjectA(env,
                                    getConstructorDeclaringClass(env, constructor),
                                    ENV FromReflectedMethod(env, constructor),
                                    value);

    free(value);

    //if Exception exists
    if (ENV ExceptionCheck(env)) {
        jthrowable t = ENV ExceptionOccurred(env);
        throwInvocationTargetException(env, t);
        return NULL;
    }

    return result;
}

/*
 * Class:     com_henryrenyz_creflect_ReflectLibImpl
 * Method:    allocInstance0
 * Signature: (Ljava/lang/Class;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_com_henryrenyz_creflect_ReflectLibImpl_allocInstance0
(JNIEnv * env, jclass cls, jclass target) {
    return ENV AllocObject(env, target);
}