/*
 * @BEGIN LICENSE
 *
 * Psi4: an open-source quantum chemistry software package
 *
 * Copyright (c) 2007-2017 The Psi4 Developers.
 *
 * The copyrights for code used from other parties are included in
 * the corresponding files.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * @END LICENSE
 */

/*!
 ** \file
 ** \ingroup PSIO
 */

#include "psi4/libpsio/psio.h"
#include "psi4/libpsio/psio.hpp"

namespace psi {
  /*!
   ** PSIO_GET_ADDRESS(): Given a starting page/offset and a shift length
   ** (in bytes), return the page/offset of the next position in the file.
   ** \ingroup PSIO
   */

  psio_address psio_get_address(psio_address start, ULI shift) {
    psio_address address;
    ULI bytes_left;

    bytes_left = PSIO_PAGELEN - start.offset; /* Bytes remaining on fpage */

    if (shift >= bytes_left) { /* Shift to later page */
      address.page = start.page + (shift - bytes_left)/PSIO_PAGELEN+ 1;
      address.offset = shift - bytes_left -(address.page - start.page- 1)
          *PSIO_PAGELEN;
    } else { /* Block starts on current page */
      address.page = start.page;
      address.offset = start.offset + shift;
    }

    return address;
  }

}
