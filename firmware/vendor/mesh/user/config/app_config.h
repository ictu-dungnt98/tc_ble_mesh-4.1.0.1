#pragma once

#ifndef __FILENAME__
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#ifndef ARR_SIZE
#define ARR_SIZE(x) sizeof(x) / sizeof(x[0])
#endif

#define APP_DFU_ID     2
#define SW_VER_MAJOR   6
#define SW_VER_MINOR   1
#define SW_VER_PATH    2
#define SW_VER_BUILD   241015

#define DEBUG_ENABLE        1
#define SDK_LOG_ENABLE      0