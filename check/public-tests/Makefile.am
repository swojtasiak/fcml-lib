noinst_PROGRAMS = fcml_public_check

fcml_public_check_SOURCES = main.c \
	error_handling_t.c \
	error_handling_t.h \
	hints_t.c \
	hints_t.h \
	instructions_a_t.c \
	instructions_a_t.h \
	instructions_base_t.c \
	instructions_base_t.h \
	instructions_b_t.c \
	instructions_b_t.h \
	instructions_c_t.c \
	instructions_c_t.h \
	instructions_d_t.c \
	instructions_d_t.h \
	instructions_e_t.c \
	instructions_e_t.h \
	instructions_f_t.c \
	instructions_f_t.h \
	instructions_g_t.c \
	instructions_g_t.h \
	instructions_h_t.c \
	instructions_h_t.h \
	instructions_i_t.c \
	instructions_i_t.h \
	instructions_j_t.c \
	instructions_j_t.h \
	instructions_l_t.c \
	instructions_l_t.h \
	instructions_m_t.c \
	instructions_m_t.h \
	instructions_n_t.c \
	instructions_n_t.h \
	instructions_o_t.c \
	instructions_o_t.h \
	instructions_p_t.c \
	instructions_p_t.h \
	instructions_r_t.c \
	instructions_r_t.h \
	instructions_s_t.c \
	instructions_s_t.h \
	instructions_t_t.c \
	instructions_t_t.h \
	instructions_u_t.c \
	instructions_u_t.h \
	instructions_v_t.c \
	instructions_v_t.h \
	instructions_w_t.c \
	instructions_w_t.h \
	instructions_x_t.c \
	instructions_x_t.h \
	prefixes_t.c \
	prefixes_t.h \
	segment_reg_t.c \
	segment_reg_t.h \
	chooser_t.c \
	chooser_t.h \
	render_t.h \
	render_t.c
	
fcml_public_check_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/check/stf @FCML_IMPORT_LIB@

fcml_public_check_LDADD = $(top_srcdir)/src/libfcml.la $(top_srcdir)/check/stf/libstf.la

check_SCRIPTS = fcml_public_check

TESTS = $(check_SCRIPTS)
