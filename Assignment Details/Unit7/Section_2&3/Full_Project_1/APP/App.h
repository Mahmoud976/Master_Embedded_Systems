#ifndef APP_H
#define APP_H

#include "Led.h"
#include "LCD.h"
#include "KeyPad.h"
#include "Button.h"
#include "GPIO.h"
#include <string.h>  // For strcmp

/* ---------- Password states ---------- */
typedef enum
{
    PASS_IDLE = 0,
    PASS_ENTER,
    PASS_CHECK,
    PASS_RESULT
} PassState_t;

/* ---------- Password length ---------- */
#define PASSWORD_LENGTH   4U

/* ---------- APIs ---------- */
void APP_Password_Init(void);
void APP_PasswordMode(void);

#endif // APP_H
