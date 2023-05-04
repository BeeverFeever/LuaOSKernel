/**
 * Copyright (C) 2023 pitulst
 *
 * This file is part of LuaOS.
 *
 * LuaOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LuaOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LuaOS.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/**
 * more info: 
 *      https://wiki.osdev.org/%228042%22_PS/2_Controller
 *
 * retrieves and processes a character from the ps2 input ports
 *
 * return char - the character after being retrieved and processed
 */
char ps2_getc(void);
