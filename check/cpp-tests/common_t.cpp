/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2014 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/* Test suite initialization. */

#include "common_t.hpp"

#include <fcml_errors.h>
#include <fcml_common.hpp>
#include <fcml_errors.hpp>
#include <fcml_registers.hpp>

using namespace fcml;

fcml_bool fcml_tf_cpp_common_suite_init(void) {
    return FCML_TRUE;
}

fcml_bool fcml_tf_cpp_common_suite_cleanup(void) {
    return FCML_TRUE;
}


void fcml_tf_cpp_integer(void) {

    Integer i1_fcml_uint8_t((fcml_uint8_t)0xFF);
    Integer i1_fcml_int8_t((fcml_int8_t)0xFF);
    Integer i1_fcml_uint16_t((fcml_uint16_t)0xFFFF);
    Integer i1_fcml_int16_t((fcml_int16_t)0xFFFF);
    Integer i1_fcml_uint32_t((fcml_uint32_t)0xFFFFFFFF);
    Integer i1_fcml_int32_t((fcml_int32_t)0xFFFFFFFF);
    Integer i1_fcml_uint64_t((fcml_uint64_t)0xFFFFFFFFFFFFFFFFUL);
    Integer i1_fcml_int64_t((fcml_int64_t)0xFFFFFFFFFFFFFFFFUL);

    STF_ASSERT_EQUAL( (fcml_uint8_t)i1_fcml_uint8_t.getInt8(), (fcml_uint8_t)0xFF );
    STF_ASSERT_EQUAL( i1_fcml_uint8_t.isSigned(), FCML_FALSE );
    STF_ASSERT_EQUAL( i1_fcml_uint8_t.getSize(), FCML_DS_8 );

    STF_ASSERT_EQUAL( (fcml_int8_t)i1_fcml_int8_t.getInt8(), (fcml_int8_t)0xFF );
    STF_ASSERT_EQUAL( i1_fcml_int8_t.isSigned(), FCML_TRUE );
    STF_ASSERT_EQUAL( i1_fcml_int8_t.getSize(), FCML_DS_8 );

    STF_ASSERT_EQUAL( (fcml_uint16_t)i1_fcml_uint16_t.getInt16(), (fcml_uint16_t)0xFFFF );
    STF_ASSERT_EQUAL( i1_fcml_uint16_t.isSigned(), FCML_FALSE );
    STF_ASSERT_EQUAL( i1_fcml_uint16_t.getSize(), FCML_DS_16 );

    STF_ASSERT_EQUAL( (fcml_int16_t)i1_fcml_int16_t.getInt16(), (fcml_int16_t)0xFFFF );
    STF_ASSERT_EQUAL( i1_fcml_int16_t.isSigned(), FCML_TRUE );
    STF_ASSERT_EQUAL( i1_fcml_int16_t.getSize(), FCML_DS_16 );

    STF_ASSERT_EQUAL( (fcml_uint32_t)i1_fcml_uint32_t.getInt32(), (fcml_uint32_t)0xFFFFFFFF );
    STF_ASSERT_EQUAL( i1_fcml_uint32_t.isSigned(), FCML_FALSE );
    STF_ASSERT_EQUAL( i1_fcml_uint32_t.getSize(), FCML_DS_32 );

    STF_ASSERT_EQUAL( (fcml_int32_t)i1_fcml_int32_t.getInt32(), (fcml_int32_t)0xFFFFFFFF );
    STF_ASSERT_EQUAL( i1_fcml_int32_t.isSigned(), FCML_TRUE );
    STF_ASSERT_EQUAL( i1_fcml_int32_t.getSize(), FCML_DS_32 );

    STF_ASSERT_EQUAL( (fcml_uint64_t)i1_fcml_uint64_t.getInt64(), (fcml_uint64_t)0xFFFFFFFFFFFFFFFFUL );
    STF_ASSERT_EQUAL( i1_fcml_uint64_t.isSigned(), FCML_FALSE );
    STF_ASSERT_EQUAL( i1_fcml_uint64_t.getSize(), FCML_DS_64 );

    STF_ASSERT_EQUAL( (fcml_int64_t)i1_fcml_int64_t.getInt64(), (fcml_int64_t)0xFFFFFFFFFFFFFFFFUL );
    STF_ASSERT_EQUAL( i1_fcml_int64_t.isSigned(), FCML_TRUE );
    STF_ASSERT_EQUAL( i1_fcml_int64_t.getSize(), FCML_DS_64 );

}

void fcml_tf_cpp_integer_operator(void) {

    Integer i1_fcml_uint8_t = (fcml_uint8_t)0xFF;
    Integer i1_fcml_int8_t = (fcml_int8_t)0xFF;
    Integer i1_fcml_uint16_t = (fcml_uint16_t)0xFFFF;
    Integer i1_fcml_int16_t = (fcml_int16_t)0xFFFF;
    Integer i1_fcml_uint32_t = (fcml_uint32_t)0xFFFFFFFF;
    Integer i1_fcml_int32_t = (fcml_int32_t)0xFFFFFFFF;
    Integer i1_fcml_uint64_t = (fcml_uint64_t)0xFFFFFFFFFFFFFFFFUL;
    Integer i1_fcml_int64_t = (fcml_int64_t)0xFFFFFFFFFFFFFFFFUL;

    STF_ASSERT_EQUAL( (fcml_uint8_t)i1_fcml_uint8_t.getInt8(), (fcml_uint8_t)0xFF );
    STF_ASSERT_EQUAL( i1_fcml_uint8_t.isSigned(), FCML_FALSE );
    STF_ASSERT_EQUAL( i1_fcml_uint8_t.getSize(), FCML_DS_8 );

    STF_ASSERT_EQUAL( (fcml_int8_t)i1_fcml_int8_t.getInt8(), (fcml_int8_t)0xFF );
    STF_ASSERT_EQUAL( i1_fcml_int8_t.isSigned(), FCML_TRUE );
    STF_ASSERT_EQUAL( i1_fcml_int8_t.getSize(), FCML_DS_8 );

    STF_ASSERT_EQUAL( (fcml_uint16_t)i1_fcml_uint16_t.getInt16(), (fcml_uint16_t)0xFFFF );
    STF_ASSERT_EQUAL( i1_fcml_uint16_t.isSigned(), FCML_FALSE );
    STF_ASSERT_EQUAL( i1_fcml_uint16_t.getSize(), FCML_DS_16 );

    STF_ASSERT_EQUAL( (fcml_int16_t)i1_fcml_int16_t.getInt16(), (fcml_int16_t)0xFFFF );
    STF_ASSERT_EQUAL( i1_fcml_int16_t.isSigned(), FCML_TRUE );
    STF_ASSERT_EQUAL( i1_fcml_int16_t.getSize(), FCML_DS_16 );

    STF_ASSERT_EQUAL( (fcml_uint32_t)i1_fcml_uint32_t.getInt32(), (fcml_uint32_t)0xFFFFFFFF );
    STF_ASSERT_EQUAL( i1_fcml_uint32_t.isSigned(), FCML_FALSE );
    STF_ASSERT_EQUAL( i1_fcml_uint32_t.getSize(), FCML_DS_32 );

    STF_ASSERT_EQUAL( (fcml_int32_t)i1_fcml_int32_t.getInt32(), (fcml_int32_t)0xFFFFFFFF );
    STF_ASSERT_EQUAL( i1_fcml_int32_t.isSigned(), FCML_TRUE );
    STF_ASSERT_EQUAL( i1_fcml_int32_t.getSize(), FCML_DS_32 );

    STF_ASSERT_EQUAL( (fcml_uint64_t)i1_fcml_uint64_t.getInt64(), (fcml_uint64_t)0xFFFFFFFFFFFFFFFFUL );
    STF_ASSERT_EQUAL( i1_fcml_uint64_t.isSigned(), FCML_FALSE );
    STF_ASSERT_EQUAL( i1_fcml_uint64_t.getSize(), FCML_DS_64 );

    STF_ASSERT_EQUAL( (fcml_int64_t)i1_fcml_int64_t.getInt64(), (fcml_int64_t)0xFFFFFFFFFFFFFFFFUL );
    STF_ASSERT_EQUAL( i1_fcml_int64_t.isSigned(), FCML_TRUE );
    STF_ASSERT_EQUAL( i1_fcml_int64_t.getSize(), FCML_DS_64 );

}

void fcml_tf_cpp_integer_copy(void) {

    Integer i1c_fcml_uint8_t = (fcml_uint8_t)0xFF;
    Integer i1c_fcml_int8_t = (fcml_int8_t)0xFF;
    Integer i1c_fcml_uint16_t = (fcml_uint16_t)0xFFFF;
    Integer i1c_fcml_int16_t = (fcml_int16_t)0xFFFF;
    Integer i1c_fcml_uint32_t = (fcml_uint32_t)0xFFFFFFFF;
    Integer i1c_fcml_int32_t = (fcml_int32_t)0xFFFFFFFF;
    Integer i1c_fcml_uint64_t = (fcml_uint64_t)0xFFFFFFFFFFFFFFFFUL;
    Integer i1c_fcml_int64_t = (fcml_int64_t)0xFFFFFFFFFFFFFFFFUL;

    Integer i1_fcml_uint8_t = i1c_fcml_uint8_t;
    Integer i1_fcml_int8_t = i1c_fcml_int8_t;
    Integer i1_fcml_uint16_t = i1c_fcml_uint16_t;
    Integer i1_fcml_int16_t = i1c_fcml_int16_t;
    Integer i1_fcml_uint32_t = i1c_fcml_uint32_t;
    Integer i1_fcml_int32_t = i1c_fcml_int32_t;
    Integer i1_fcml_uint64_t = i1c_fcml_uint64_t;
    Integer i1_fcml_int64_t = i1c_fcml_int64_t;

    i1c_fcml_uint8_t = 0;
    i1c_fcml_int8_t = 0;
    i1c_fcml_uint16_t = 0;
    i1c_fcml_int16_t = 0;
    i1c_fcml_uint32_t = 0;
    i1c_fcml_int32_t = 0;
    i1c_fcml_uint64_t = 0;
    i1c_fcml_int64_t = 0;

    STF_ASSERT_EQUAL( (fcml_uint8_t)i1_fcml_uint8_t.getInt8(), (fcml_uint8_t)0xFF );
    STF_ASSERT_EQUAL( i1_fcml_uint8_t.isSigned(), FCML_FALSE );
    STF_ASSERT_EQUAL( i1_fcml_uint8_t.getSize(), FCML_DS_8 );

    STF_ASSERT_EQUAL( (fcml_int8_t)i1_fcml_int8_t.getInt8(), (fcml_int8_t)0xFF );
    STF_ASSERT_EQUAL( i1_fcml_int8_t.isSigned(), FCML_TRUE );
    STF_ASSERT_EQUAL( i1_fcml_int8_t.getSize(), FCML_DS_8 );

    STF_ASSERT_EQUAL( (fcml_uint16_t)i1_fcml_uint16_t.getInt16(), (fcml_uint16_t)0xFFFF );
    STF_ASSERT_EQUAL( i1_fcml_uint16_t.isSigned(), FCML_FALSE );
    STF_ASSERT_EQUAL( i1_fcml_uint16_t.getSize(), FCML_DS_16 );

    STF_ASSERT_EQUAL( (fcml_int16_t)i1_fcml_int16_t.getInt16(), (fcml_int16_t)0xFFFF );
    STF_ASSERT_EQUAL( i1_fcml_int16_t.isSigned(), FCML_TRUE );
    STF_ASSERT_EQUAL( i1_fcml_int16_t.getSize(), FCML_DS_16 );

    STF_ASSERT_EQUAL( (fcml_uint32_t)i1_fcml_uint32_t.getInt32(), (fcml_uint32_t)0xFFFFFFFF );
    STF_ASSERT_EQUAL( i1_fcml_uint32_t.isSigned(), FCML_FALSE );
    STF_ASSERT_EQUAL( i1_fcml_uint32_t.getSize(), FCML_DS_32 );

    STF_ASSERT_EQUAL( (fcml_int32_t)i1_fcml_int32_t.getInt32(), (fcml_int32_t)0xFFFFFFFF );
    STF_ASSERT_EQUAL( i1_fcml_int32_t.isSigned(), FCML_TRUE );
    STF_ASSERT_EQUAL( i1_fcml_int32_t.getSize(), FCML_DS_32 );

    STF_ASSERT_EQUAL( (fcml_uint64_t)i1_fcml_uint64_t.getInt64(), (fcml_uint64_t)0xFFFFFFFFFFFFFFFFUL );
    STF_ASSERT_EQUAL( i1_fcml_uint64_t.isSigned(), FCML_FALSE );
    STF_ASSERT_EQUAL( i1_fcml_uint64_t.getSize(), FCML_DS_64 );

    STF_ASSERT_EQUAL( (fcml_int64_t)i1_fcml_int64_t.getInt64(), (fcml_int64_t)0xFFFFFFFFFFFFFFFFUL );
    STF_ASSERT_EQUAL( i1_fcml_int64_t.isSigned(), FCML_TRUE );
    STF_ASSERT_EQUAL( i1_fcml_int64_t.getSize(), FCML_DS_64 );

}

void fcml_tf_cpp_integer_casting(void) {

    Integer i1c_fcml_uint8_t = (fcml_uint8_t)0xFF;
    Integer i1c_fcml_int8_t = (fcml_int8_t)0xFF;
    Integer i1c_fcml_uint16_t = (fcml_uint16_t)0xFFFF;
    Integer i1c_fcml_int16_t = (fcml_int16_t)0xFFFF;
    Integer i1c_fcml_uint32_t = (fcml_uint32_t)0xFFFFFFFF;
    Integer i1c_fcml_int32_t = (fcml_int32_t)0xFFFFFFFF;
    Integer i1c_fcml_uint64_t = (fcml_uint64_t)0xFFFFFFFFFFFFFFFFUL;
    Integer i1c_fcml_int64_t = (fcml_int64_t)0xFFFFFFFFFFFFFFFFUL;

    fcml_uint8_t  i1_fcml_uint8_t  = i1c_fcml_uint8_t;
    fcml_int8_t   i1_fcml_int8_t   = i1c_fcml_int8_t;
    fcml_uint16_t i1_fcml_uint16_t = i1c_fcml_uint16_t;
    fcml_int16_t  i1_fcml_int16_t  = i1c_fcml_int16_t;
    fcml_uint32_t i1_fcml_uint32_t = i1c_fcml_uint32_t;
    fcml_int32_t  i1_fcml_int32_t  = i1c_fcml_int32_t;
    fcml_uint64_t i1_fcml_uint64_t = i1c_fcml_uint64_t;
    fcml_int64_t  i1_fcml_int64_t  = i1c_fcml_int64_t;

    STF_ASSERT_EQUAL( i1_fcml_uint8_t, (fcml_uint8_t)0xFF );
    STF_ASSERT_EQUAL( i1_fcml_int8_t, (fcml_int8_t)0xFF );
    STF_ASSERT_EQUAL( i1_fcml_uint16_t, (fcml_uint16_t)0xFFFF );
    STF_ASSERT_EQUAL( i1_fcml_int16_t, (fcml_int16_t)0xFFFF );
    STF_ASSERT_EQUAL( i1_fcml_uint32_t, (fcml_uint32_t)0xFFFFFFFF );
    STF_ASSERT_EQUAL( i1_fcml_int32_t, (fcml_int32_t)0xFFFFFFFF );
    STF_ASSERT_EQUAL( i1_fcml_uint64_t, (fcml_uint64_t)0xFFFFFFFFFFFFFFFFUL );
    STF_ASSERT_EQUAL( i1_fcml_int64_t, (fcml_int64_t)0xFFFFFFFFFFFFFFFFUL );

    // Conversion.

    fcml_uint8_t conveted = i1c_fcml_int64_t;
    STF_ASSERT_EQUAL( conveted, (fcml_uint8_t)0xFF );

}

void fcml_tf_cpp_integer_comparisions(void) {

    Integer int1 = (fcml_int16_t)-1;
    Integer int2 = (fcml_int8_t)-1;
    Integer int3 = (fcml_int8_t)18;

    STF_ASSERT( int1 == int2 );
    STF_ASSERT( !(int1 != int2) );
    STF_ASSERT( int1 != int3 );

    Integer int4 = (fcml_uint8_t)0xFF;
    Integer int5 = (fcml_uint16_t)0xFFFF;
    Integer int6 = (fcml_uint32_t)0xFFFF;

    STF_ASSERT( int4 != int5 );
    STF_ASSERT( int5 == int6 );
}

void fcml_tf_cpp_integer_expressions(void) {

    const Integer i1c_fcml_uint8_t = (fcml_uint8_t)0xFF;
    const Integer i1c_fcml_int64_t = (fcml_int64_t)0xFFFFFFFFFFFFFFFFUL;

    // 255 + -1 = 254

    const Integer resultInt = i1c_fcml_int64_t + i1c_fcml_uint8_t;

    STF_ASSERT_EQUAL( resultInt.getSize(), FCML_DS_64 );
    STF_ASSERT_EQUAL( resultInt.isSigned(), FCML_TRUE );
    STF_ASSERT_EQUAL( resultInt.getInt64(), (fcml_int64_t)254 );

    fcml_uint8_t result  = i1c_fcml_int64_t + i1c_fcml_uint8_t;

    STF_ASSERT_EQUAL( result, (fcml_uint8_t)254 );

    Integer i1i_fcml_uint8_t = (fcml_uint8_t)4;
    Integer i1i_fcml_int64_t = (fcml_int64_t)8;

    result  = i1i_fcml_int64_t / i1i_fcml_uint8_t;

    STF_ASSERT_EQUAL( result, (fcml_uint8_t)2 );

    result  = i1i_fcml_int64_t * i1i_fcml_uint8_t;

    STF_ASSERT_EQUAL( result, (fcml_uint8_t)32 );

    result  = i1i_fcml_int64_t - i1i_fcml_uint8_t;

    STF_ASSERT_EQUAL( result, (fcml_uint8_t)4 );

    Integer op_pp;

    op_pp += 10;

    STF_ASSERT_EQUAL( (fcml_uint64_t)op_pp.getInt64(), (fcml_uint64_t)10 );

    op_pp *= 2;

    STF_ASSERT_EQUAL( (fcml_uint64_t)op_pp.getInt64(), (fcml_uint64_t)20 );

    op_pp /= 4;

    STF_ASSERT_EQUAL( (fcml_uint64_t)op_pp.getInt64(), (fcml_uint64_t)5 );

    op_pp -= 1;

    STF_ASSERT_EQUAL( (fcml_uint64_t)op_pp.getInt64(), (fcml_uint64_t)4 );

    Integer value_1((fcml_uint8_t)0xFE);
	Integer value_2((fcml_uint8_t)0x01);
	Integer value_3 = value_1 + value_2;

	value_1 = *(&value_2);

	STF_ASSERT_EQUAL( value_3.getSize(), FCML_DS_8 );
	STF_ASSERT_EQUAL( value_3.isSigned(), FCML_FALSE );
	STF_ASSERT_EQUAL( (fcml_uint8_t)value_3.getInt8(), (fcml_uint8_t)0xFF );

}

void fcml_tf_cpp_integer_example(void) {

    Integer v1 = static_cast<fcml_uint8_t>( 10 );
    Integer v2 = static_cast<fcml_uint8_t>( 20 );

    fcml_uint8_t sum = v1 + v2;

    STF_ASSERT( sum == 30 );

}

void fcml_tf_cpp_integer_example_1(void) {

    Integer v1 = (fcml_int64_t)10;
    Integer v2 = (fcml_uint8_t)20;

    Integer sum = v2 + v1;

    STF_ASSERT( sum == 30 );
    STF_ASSERT( !sum.isSigned() );
    STF_ASSERT_EQUAL( sum.getSize(), 8 );

}

void fcml_tf_cpp_registers(void) {

    const Register &reg = AL;

    if( reg == Register::AL() ) {
        STF_ASSERT( true );
    }

    STF_ASSERT_EQUAL( reg.getReg(), FCML_REG_AL );
    STF_ASSERT_EQUAL( reg.getSize(), FCML_DS_8 );
    STF_ASSERT_EQUAL( reg.getType(), Register::REG_GPR );
    STF_ASSERT_EQUAL( reg.getX64Exp(), FCML_FALSE );

    Register regCons( FCML_REG_AL, FCML_DS_8 );

    STF_ASSERT_EQUAL( regCons.getReg(), FCML_REG_AL );
    STF_ASSERT_EQUAL( regCons.getSize(), FCML_DS_8 );
    STF_ASSERT_EQUAL( regCons.getType(), Register::REG_GPR );
    STF_ASSERT_EQUAL( regCons.getX64Exp(), FCML_FALSE );

    STF_ASSERT( Register::EAX() == EAX );
    STF_ASSERT( !(Register::EAX() == Register::ECX()) );
    STF_ASSERT( Register::EAX() != Register::EBX() );
    STF_ASSERT( !(Register::EAX() != Register::EAX()) );
}

void fcml_tf_cpp_far_pointer(void) {

    FarPointer fp = FarPointer(0x3000, 0x000401000 );

    STF_ASSERT_EQUAL( fp.getSegment(), 0x3000 );
    STF_ASSERT_EQUAL( fp.getOffset16(), 0x0000 );
    STF_ASSERT_EQUAL( fp.getOffset32(), 0x000401000 );
    STF_ASSERT_EQUAL( fp.getOffsetSize(), FCML_DS_32 );

    fp = FarPointer::off32( 0x3000, 0x000401000 );

    STF_ASSERT_EQUAL( fp.getSegment(), 0x3000 );
    STF_ASSERT_EQUAL( fp.getOffset16(), 0x0000 );
    STF_ASSERT_EQUAL( fp.getOffset32(), 0x000401000 );
    STF_ASSERT_EQUAL( fp.getOffsetSize(), FCML_DS_32 );

    fp = FarPointer(0x3000, (fcml_int16_t)0x1212 );

    STF_ASSERT_EQUAL( fp.getSegment(), 0x3000 );
    STF_ASSERT_EQUAL( fp.getOffset16(), 0x1212 );
    STF_ASSERT_EQUAL( fp.getOffset32(), 0x0000 );
    STF_ASSERT_EQUAL( fp.getOffsetSize(), FCML_DS_16 );

    fp = FarPointer::off16( 0x3000, 0x01212 );

    STF_ASSERT_EQUAL( fp.getSegment(), 0x3000 );
    STF_ASSERT_EQUAL( fp.getOffset16(), 0x1212 );
    STF_ASSERT_EQUAL( fp.getOffset32(), 0x0000 );
    STF_ASSERT_EQUAL( fp.getOffsetSize(), FCML_DS_16 );

}

void fcml_tf_cpp_segment_selector(void) {
    SegmentSelector ss(Register::CS(),true);
    STF_ASSERT_EQUAL( ss.getSegmentSelector().getReg(), FCML_REG_CS );
    ss = EAX;
    STF_ASSERT_EQUAL( ss.getSegmentSelector().getReg(), FCML_REG_EAX );
    Register reg;
    reg = ss;
    STF_ASSERT_EQUAL( reg.getReg(), FCML_REG_EAX );
}

void fcml_tf_cpp_effective_address(void) {

    EffectiveAddress empty;
    STF_ASSERT_EQUAL( empty.getBase(), Register::UNDEF() );
    STF_ASSERT_EQUAL( empty.getIndex(), Register::UNDEF() );
    STF_ASSERT_EQUAL( empty.getScaleFactor(), (fcml_uint8_t)0 );
    STF_ASSERT_EQUAL( empty.getDisplacement(), Integer() );

    EffectiveAddress base( Register::EAX() );
    STF_ASSERT_EQUAL( base.getBase(), Register::EAX() );
    STF_ASSERT_EQUAL( base.getIndex(), Register::UNDEF() );
    STF_ASSERT_EQUAL( base.getScaleFactor(), 0 );
    STF_ASSERT_EQUAL( base.getDisplacement(), Integer::int8(0) );

    EffectiveAddress base_disp( Register::EAX(), Integer::int8(67) );
    STF_ASSERT_EQUAL( base_disp.getBase(), Register::EAX() );
    STF_ASSERT_EQUAL( base_disp.getIndex(), Register::UNDEF() );
    STF_ASSERT_EQUAL( base_disp.getScaleFactor(), 0 );
    STF_ASSERT_EQUAL( base_disp.getDisplacement(), Integer::int8(67) );

    EffectiveAddress index_scale_disp( Register::EAX(), 4, Integer::int32(400) );
    STF_ASSERT_EQUAL( index_scale_disp.getBase(), Register::UNDEF() );
    STF_ASSERT_EQUAL( index_scale_disp.getIndex(), Register::EAX() );
    STF_ASSERT_EQUAL( index_scale_disp.getScaleFactor(), 4 );
    STF_ASSERT_EQUAL( index_scale_disp.getDisplacement(), Integer::int16(400) );

    EffectiveAddress base_index( Register::EAX(), Register::ECX() );
    STF_ASSERT_EQUAL( base_index.getBase(), Register::EAX() );
    STF_ASSERT_EQUAL( base_index.getIndex(), Register::ECX() );
    STF_ASSERT_EQUAL( base_index.getScaleFactor(), 0 );
    STF_ASSERT_EQUAL( base_index.getDisplacement(), Integer::int8(0) );

    EffectiveAddress base_index_scale( Register::EAX(), Register::ECX(), 4 );
    STF_ASSERT_EQUAL( base_index_scale.getBase(), Register::EAX() );
    STF_ASSERT_EQUAL( base_index_scale.getIndex(), Register::ECX() );
    STF_ASSERT_EQUAL( base_index_scale.getScaleFactor(), 4 );

    EffectiveAddress full( Register::EAX(), Register::EDX(), 1, Integer::int8(67) );
    STF_ASSERT_EQUAL( full.getBase(), Register::EAX() );
    STF_ASSERT_EQUAL( full.getIndex(), Register::EDX() );
    STF_ASSERT_EQUAL( full.getScaleFactor(), 1 );
    STF_ASSERT_EQUAL( full.getDisplacement(), Integer::int8(67) );
}

void fcml_tf_cpp_effective_address_factory_methods(void) {

    EffectiveAddress base = EffectiveAddress::addr( Register::EAX() );
    STF_ASSERT_EQUAL( base.getBase(), Register::EAX() );
    STF_ASSERT_EQUAL( base.getIndex(), Register::UNDEF() );
    STF_ASSERT_EQUAL( base.getScaleFactor(), 0 );
    STF_ASSERT_EQUAL( base.getDisplacement(), Integer::int8(0) );

    EffectiveAddress base_disp = EffectiveAddress::addr( Register::EAX(), Integer::int8(67) );
    STF_ASSERT_EQUAL( base_disp.getBase(), Register::EAX() );
    STF_ASSERT_EQUAL( base_disp.getIndex(), Register::UNDEF() );
    STF_ASSERT_EQUAL( base_disp.getScaleFactor(), 0 );
    STF_ASSERT_EQUAL( base_disp.getDisplacement(), Integer::int8(67) );

    EffectiveAddress index_scale_disp = EffectiveAddress::addr( Register::EAX(), 4, Integer::int32(400) );
    STF_ASSERT_EQUAL( index_scale_disp.getBase(), Register::UNDEF() );
    STF_ASSERT_EQUAL( index_scale_disp.getIndex(), Register::EAX() );
    STF_ASSERT_EQUAL( index_scale_disp.getScaleFactor(), 4 );
    STF_ASSERT_EQUAL( index_scale_disp.getDisplacement(), Integer::int16(400) );

    EffectiveAddress base_index = EffectiveAddress::addr( Register::EAX(), Register::ECX() );
    STF_ASSERT_EQUAL( base_index.getBase(), Register::EAX() );
    STF_ASSERT_EQUAL( base_index.getIndex(), Register::ECX() );
    STF_ASSERT_EQUAL( base_index.getScaleFactor(), 0 );
    STF_ASSERT_EQUAL( base_index.getDisplacement(), Integer::int8(0) );

    EffectiveAddress base_index_scale = EffectiveAddress::addr( Register::EAX(), Register::ECX(), 4 );
    STF_ASSERT_EQUAL( base_index_scale.getBase(), Register::EAX() );
    STF_ASSERT_EQUAL( base_index_scale.getIndex(), Register::ECX() );
    STF_ASSERT_EQUAL( base_index_scale.getScaleFactor(), 4 );

    EffectiveAddress full = EffectiveAddress::addr( Register::EAX(), Register::EDX(), 1, Integer::int8(67) );
    STF_ASSERT_EQUAL( full.getBase(), Register::EAX() );
    STF_ASSERT_EQUAL( full.getIndex(), Register::EDX() );
    STF_ASSERT_EQUAL( full.getScaleFactor(), 1 );
    STF_ASSERT_EQUAL( full.getDisplacement(), Integer::int8(67) );
}

void fcml_tf_cpp_address(void) {

    Address address((fcml_uint32_t)0x401000);
    STF_ASSERT_EQUAL( address.getAddressForm(), Address::AF_OFFSET );
    STF_ASSERT_EQUAL( address.getSizeOperator(), FCML_DS_UNDEF );
    STF_ASSERT_EQUAL( address.isOffset(), true );
    STF_ASSERT( address.getOffset().getInt32() == 0x401000 );
    STF_ASSERT_EQUAL( address.getOffset().getSize(), FCML_DS_32 );
    STF_ASSERT_EQUAL( address.isEffectiveAddress(), false );

    Address addressEffective(EffectiveAddress::addr(Register::EAX()), FCML_DS_32);
    STF_ASSERT_EQUAL( addressEffective.getAddressForm(), Address::AF_COMBINED );
    STF_ASSERT_EQUAL( addressEffective.getSizeOperator(), FCML_DS_32 );
    STF_ASSERT_EQUAL( addressEffective.isOffset(), false );
    STF_ASSERT_EQUAL( addressEffective.getEffectiveAddress().getBase(), Register::EAX() );
    STF_ASSERT_EQUAL( addressEffective.isEffectiveAddress(), true );

    addressEffective = Address::effective(EAX, FCML_DS_32);
    STF_ASSERT_EQUAL( addressEffective.getAddressForm(), Address::AF_COMBINED );
    STF_ASSERT_EQUAL( addressEffective.getSizeOperator(), FCML_DS_32 );
    STF_ASSERT_EQUAL( addressEffective.isOffset(), false );
    STF_ASSERT_EQUAL( addressEffective.getEffectiveAddress().getBase(), Register::EAX() );
    STF_ASSERT_EQUAL( addressEffective.isEffectiveAddress(), true );
}


void fcml_tf_cpp_condition() {
    Condition condition( Condition::CONDITION_LE, true );
    STF_ASSERT_EQUAL( condition, Condition::NLE() );
    if( condition.isNLE() && condition.isNegation() ) {
        STF_ASSERT( true );
    } else {
        STF_ASSERT( false );
    }
    if( condition == Condition::NLE() ) {
        STF_ASSERT( true );
    } else {
        STF_ASSERT( false );
    }
}

void fcml_tf_cpp_operand() {

    Operand imm(0x201000);
    STF_ASSERT( imm.getImmediate() == (fcml_int32_t)0x201000 );
    STF_ASSERT( imm.isImm() );

    Operand far_ptr(FarPointer(0x1020, (fcml_int16_t)0x3030));
    STF_ASSERT( far_ptr.getFarPointer().getSegment() == (fcml_int16_t)0x1020 );
    STF_ASSERT( far_ptr.getFarPointer().getOffset16() == (fcml_int16_t)0x3030 );
    STF_ASSERT( far_ptr.isFar() );

    Operand operandImm = OB::imm( 0x401000 );
    fcml_uint32_t value = operandImm.getImmediate();
    STF_ASSERT_EQUAL( value, 0x401000 );

    Operand operand;
    operand.far_ptr(FarPointer(0x1020, (fcml_int16_t)0x3030));
    STF_ASSERT( operand.getFarPointer().getSegment() == (fcml_int16_t)0x1020 );
    STF_ASSERT( operand.getFarPointer().getOffset16() == (fcml_int16_t)0x3030 );
    STF_ASSERT( operand.isFar() );

    operand = OB::far_ptr(0x1020, (fcml_int16_t)0x3030);
    STF_ASSERT( operand.getFarPointer().getSegment() == (fcml_int16_t)0x1020 );
    STF_ASSERT( operand.getFarPointer().getOffset16() == (fcml_int16_t)0x3030 );
    STF_ASSERT( operand.isFar() );

    Operand addrSimple = OB::addr(EffectiveAddress(Register::EAX()));
    STF_ASSERT( addrSimple.getAddress().isEffectiveAddress() );
    STF_ASSERT_EQUAL( addrSimple.getAddress().getEffectiveAddress().getBase(), Register::EAX() );
    STF_ASSERT( addrSimple.isAddr() );

    Operand operandEA;
    operandEA.addr(EffectiveAddress(Register::EAX()));
    STF_ASSERT( operandEA.getAddress().isEffectiveAddress() );
    STF_ASSERT_EQUAL( operandEA.getAddress().getEffectiveAddress().getBase(), Register::EAX() );
    STF_ASSERT( operandEA.isAddr() );

	Operand address = Operand(Address(EffectiveAddress(Register::EAX())));
    STF_ASSERT( address.getAddress().isEffectiveAddress() );
    STF_ASSERT_EQUAL( address.getAddress().getEffectiveAddress().getBase(), Register::EAX() );
    STF_ASSERT( address.isAddr() );

    Operand regSimple = OB::reg(Register::EAX());
    STF_ASSERT( regSimple.isReg() );
    STF_ASSERT_EQUAL( regSimple.getRegister(), Register::EAX() );
}

void fcml_tf_cpp_entry_point() {
    EntryPoint entryPoint( EntryPoint::OM_32_BIT, 0x401000 );
    STF_ASSERT_EQUAL( entryPoint.getOpMode(), EntryPoint::OM_32_BIT );
    STF_ASSERT_EQUAL( entryPoint.getIP(), 0x401000 );

}

fcml_stf_test_case fcml_ti_cpp_common[] = {
    { "fcml_tf_cpp_integer", fcml_tf_cpp_integer },
    { "fcml_tf_cpp_integer_operator", fcml_tf_cpp_integer_operator },
    { "fcml_tf_cpp_integer_casting", fcml_tf_cpp_integer_casting },
    { "fcml_tf_cpp_integer_expressions", fcml_tf_cpp_integer_expressions },
    { "fcml_tf_cpp_integer_comparisions", fcml_tf_cpp_integer_comparisions },
    { "fcml_tf_cpp_registers", fcml_tf_cpp_registers },
    { "fcml_tf_cpp_far_pointer", fcml_tf_cpp_far_pointer },
    { "fcml_tf_cpp_effective_address", fcml_tf_cpp_effective_address },
    { "fcml_tf_cpp_effective_address_factory_methods", fcml_tf_cpp_effective_address_factory_methods },
    { "fcml_tf_cpp_address", fcml_tf_cpp_address },
    { "fcml_tf_cpp_operand", fcml_tf_cpp_operand },
    { "fcml_tf_cpp_segment_selector", fcml_tf_cpp_segment_selector },
    { "fcml_tf_cpp_entry_point", fcml_tf_cpp_entry_point },
    { "fcml_tf_cpp_integer_example", fcml_tf_cpp_integer_example },
    { "fcml_tf_cpp_integer_example_1", fcml_tf_cpp_integer_example_1 },
    { "fcml_tf_cpp_condition", fcml_tf_cpp_condition },
    FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_cpp_common = {
    "suite-fcml-cpp-common", fcml_tf_cpp_common_suite_init, fcml_tf_cpp_common_suite_cleanup, fcml_ti_cpp_common
};
