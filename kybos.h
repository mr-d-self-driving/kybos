/*
 * kybos.h
 *
 * Copyright 2015 Stefan Rupp (struppi@struppi.name)
 *
 * This file is part of kybos.
 *
 * kybos is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * kybos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with kybos.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef KYBOS_H_
#define KYBOS_H_


#if defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC) || \
    defined (STM32L151xB) || defined (STM32L151xBA) || defined (STM32L151xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L151xDX) || defined (STM32L151xE) || \
    defined (STM32L152xB) || defined (STM32L152xBA) || defined (STM32L152xC) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L152xDX) || defined (STM32L152xE) || \
    defined (STM32L162xC) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L162xDX) || defined (STM32L162xE)

#define STM32_FAMILY stm32l1xx

#elif defined (STM32F405xx) || defined (STM32F415xx) || defined (STM32F407xx) || defined (STM32F417xx) || \
    defined (STM32F427xx) || defined (STM32F437xx) || defined (STM32F429xx) || defined (STM32F439xx) || \
    defined (STM32F401xC) || defined (STM32F401xE) || defined (STM32F411xE)


#define STM32_FAMILY stm32f4xx

#endif



#if defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L151xDX) || defined (STM32L152xE) || defined (STM32L152xDX) || defined (STM32L162xE) || defined (STM32L162xDX) || defined (STM32F429xx)
#define HAS_GPIO_A
#define HAS_GPIO_B
#define HAS_GPIO_C
#define HAS_GPIO_D
#define HAS_GPIO_E
#define HAS_GPIO_F
#define HAS_GPIO_G
#define HAS_GPIO_H

#if defined (STM32F429xx)
#define HAS_GPIO_I
#define HAS_GPIO_J
#define HAS_GPIO_K
#endif
#endif

#if defined (STM32L151xB) || defined (STM32L151xBA) || defined (STM32L151xC) || defined (STM32L152xB) || defined (STM32L152xBA) || defined (STM32L152xC) || defined (STM32L162xC)
#define HAS_GPIO_A
#define HAS_GPIO_B
#define HAS_GPIO_C
#define HAS_GPIO_D
#define HAS_GPIO_E
#define HAS_GPIO_H
#endif

#if defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC)
#define HAS_GPIO_A
#define HAS_GPIO_B
#define HAS_GPIO_C
#define HAS_GPIO_D
#define HAS_GPIO_H
#define HAS_GPIO_I
#endif



#if defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC) ||\
    defined (STM32L152xB) || defined (STM32L152xBA) || defined (STM32L152xC) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L152xE) || defined (STM32L152xDX) ||\
    defined (STM32L162xC) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L162xE) || defined (STM32L162xDX)
#define HAS_LCD_CONTROLLER
#endif


// This macro is used to generate include paths
// as HAL file names are generally based on the STM32 family's name
// It's ugly, but it works
// example:
// GENERATE_HAL_INCLUDE(STM32_FAMILY, rcc)
// expands to:
// #include <stm32l1xx_hal_rcc.h>
#define GENERATE_HAL_INCLUDE(family, module) GENERATE_HAL_INCLUDE_xpand(family, module)
#define GENERATE_HAL_INCLUDE_xpand(family, module) <family##_hal##module.h>



#endif // KYBOS_H_

