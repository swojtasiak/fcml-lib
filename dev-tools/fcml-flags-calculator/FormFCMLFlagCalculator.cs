using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ira_flags_calc
{
    public partial class FormCalculator : Form
    {
        enum Prefixes : int 
        {
            _F0,
            _F2,
            _F3,
            _W_1,
            _W_0,
            _VEXL_1,
            _VEX_LEG,
            _VEX_Required,
            _VEX_VVVV_Unused,
            _VEX_L_Ignore_For_Size,
            _XOP_Required,
            _HAL,
            _66_Man,
            _F2_Man,
            _F3_Man,
            Sufix 
        }

        enum Opcodes : int
        {
            _Reg,
            _w,
            _s,
            _sreg2,
            _sreg3,
            _eeee,
            _tttn,
            _64_Bit_EOSA_Default,
            _FIELD_POSITION_MODIFY_1,
            _FIELD_POSITION_MODIFY_2,
            _FIELD_POSITION_MODIFY_3,
            _MODRM_reg_1,
            _MODRM_reg_2,
            _MODRM_reg_3,
            _REX_FIELD_R,
            _MOD_RM_EXISTS,
            _MOD_RM_reg_EXISTS,
            AllowModRmMod3,
            _Opcode_bytes_1,
            _Opcode_bytes_2,
            _Primary_Opcode_Index_1,
            _Primary_Opcode_Index_2,
            _1632_bit_mode_supported,
            _64_bit_mode_supported,
            EOSA_16,
            EOSA_32,
            EOSA_64,
            EASA_16,
            EASA_32,
            EASA_64,
            _In64BitModeForceEOSATo64,
            AllowModRmModNot3
        }

        private bool ignoreEvents = false;

        public FormCalculator()
        {
            InitializeComponent();
            comboBoxC4_1_MMMM.SelectedIndex = 0;
            comboBoxC4_2_PP.SelectedIndex = 0;
            comboBoxC4_2_VVVV.SelectedIndex = 0;
            comboBoxC5_PP.SelectedIndex = 0;
            comboBoxC5_VVVV.SelectedIndex = 0;
        }

        void MapPrefixesToCheckBoxes()
        {
            string value = textBoxPrefixes.Text;
            ushort prefixes = (ushort)Convert.ToInt16(value, 16);
            checkBoxF0.Checked = ( (int)prefixes & ( 1 << (int)Prefixes._F0 ) ) != 0;
            checkBoxF2.Checked = ((int)prefixes & (1 << (int)Prefixes._F2)) != 0;
            checkBoxF3.Checked = ((int)prefixes & (1 << (int)Prefixes._F3)) != 0;
            checkBox_REXW_1.Checked = ((int)prefixes & (1 << (int)Prefixes._W_1)) != 0;
            checkBox_VEXW_1.Checked = ((int)prefixes & (1 << (int)Prefixes._W_0)) != 0;
            checkBox_VEXL_1.Checked = ((int)prefixes & (1 << (int)Prefixes._VEXL_1)) != 0;
            checkBox_VEX_For_Legacy.Checked = ( (int)prefixes & ( 1 << (int)Prefixes._VEX_LEG ) ) != 0;
            checkBox_VEX_NEDDED.Checked = ((int)prefixes & (1 << (int)Prefixes._VEX_Required)) != 0;
            checkBox_VVVV_Unused.Checked = ((int)prefixes & (1 << (int)Prefixes._VEX_VVVV_Unused)) != 0;
            checkBox_Reserved_3.Checked = ((int)prefixes & (1 << (int)Prefixes._VEX_L_Ignore_For_Size)) != 0;
            checkBox_XOP_Required.Checked = ((int)prefixes & (1 << (int)Prefixes._XOP_Required)) != 0;
            checkBox_EanableHAL.Checked = ((int)prefixes & (1 << (int)Prefixes._HAL)) != 0;
            checkBox66_Mand.Checked = ((int)prefixes & (1 << (int)Prefixes._66_Man)) != 0;
            checkBox_F2_Mand.Checked = ((int)prefixes & (1 << (int)Prefixes._F2_Man)) != 0;
            checkBox_F3_Mand.Checked = ((int)prefixes & (1 << (int)Prefixes._F3_Man)) != 0;
            checkBox_Suffix.Checked = ((int)prefixes & (1 << (int)Prefixes.Sufix)) != 0;
        }

        void MapCheckBoxesToPrefixes()
        {
            ushort value = 0;
            value |= (ushort)(checkBoxF0.Checked ? ( 1 << (int)Prefixes._F0 ) : 0 );
            value |= (ushort)(checkBoxF2.Checked ? (1 << (int)Prefixes._F2) : 0);
            value |= (ushort)(checkBoxF3.Checked ? (1 << (int)Prefixes._F3) : 0);
            value |= (ushort)(checkBox_REXW_1.Checked ? (1 << (int)Prefixes._W_1) : 0);
            value |= (ushort)(checkBox_VEXW_1.Checked ? (1 << (int)Prefixes._W_0) : 0);
            value |= (ushort)(checkBox_VEXL_1.Checked ? (1 << (int)Prefixes._VEXL_1) : 0);
            value |= (ushort)(checkBox_VEX_For_Legacy.Checked ? (1 << (int)Prefixes._VEX_LEG) : 0);
            value |= (ushort)(checkBox_VEX_NEDDED.Checked ? (1 << (int)Prefixes._VEX_Required) : 0);
            value |= (ushort)(checkBox_VVVV_Unused.Checked ? (1 << (int)Prefixes._VEX_VVVV_Unused) : 0);
            value |= (ushort)(checkBox_Reserved_3.Checked ? (1 << (int)Prefixes._VEX_L_Ignore_For_Size) : 0);
            value |= (ushort)(checkBox_XOP_Required.Checked ? (1 << (int)Prefixes._XOP_Required) : 0);
            value |= (ushort)(checkBox_EanableHAL.Checked ? (1 << (int)Prefixes._HAL) : 0);
            value |= (ushort)(checkBox66_Mand.Checked ? (1 << (int)Prefixes._66_Man) : 0);
            value |= (ushort)(checkBox_F2_Mand.Checked ? (1 << (int)Prefixes._F2_Man) : 0);
            value |= (ushort)(checkBox_F3_Mand.Checked ? (1 << (int)Prefixes._F3_Man) : 0);
            value |= (ushort)(checkBox_Suffix.Checked ? (1 << (int)Prefixes.Sufix) : 0);
            textBoxPrefixes.Text = "0x" + value.ToString("X4");
        }

        void MapCheckBoxesToOpcodes()
        {
            uint value = 0;
            value |= (uint)(checkBoxOpcodeFieldReg.Checked ? (1 << (int)Opcodes._Reg) : 0);
            value |= (uint)(checkBoxOpcodeFieldW.Checked ? (1 << (int)Opcodes._w) : 0);
            value |= (uint)(checkBoxOpcodeFieldS.Checked ? (1 << (int)Opcodes._s) : 0);
            value |= (uint)(checkBoxOpcodeFieldSreg2.Checked ? (1 << (int)Opcodes._sreg2) : 0);
            value |= (uint)(checkBoxOpcodeFieldSreg3.Checked ? (1 << (int)Opcodes._sreg3) : 0);
            value |= (uint)(checkBoxOpcodeFieldEEEE.Checked ? (1 << (int)Opcodes._eeee) : 0);
            value |= (uint)(checkBoxOpcodeFieldTTTN.Checked ? (1 << (int)Opcodes._tttn) : 0);
            value |= (uint)(checkBoxDefaultEOSA_64.Checked ? (1 << (int)Opcodes._64_Bit_EOSA_Default) : 0);

            value |= (uint)(checkBoxREX_field_R.Checked ? (1 << (int)Opcodes._REX_FIELD_R) : 0);
            value |= (uint)(checkBoxOpcodeField_ModRM_reg_0.Checked ? (1 << (int)Opcodes._MODRM_reg_1) : 0);
            value |= (uint)(checkBoxOpcodeField_ModRM_reg_1.Checked ? (1 << (int)Opcodes._MODRM_reg_2) : 0);
            value |= (uint)(checkBoxOpcodeField_ModRM_reg_2.Checked ? (1 << (int)Opcodes._MODRM_reg_3) : 0);

            value |= (uint)(checkBoxOpcodeField_ModRM_exists.Checked ? (1 << (int)Opcodes._MOD_RM_EXISTS) : 0);
            value |= (uint)(checkBoxOpcodeField_ModRM_reg_exists.Checked ? (1 << (int)Opcodes._MOD_RM_reg_EXISTS) : 0);
            // value |= (uint)(checkBoxOpcodeField_ModRM_REX_R_exists.Checked ? (1 << (int)Opcodes._REX_FIELD_R_EXISTS) : 0);
            value |= (uint)(checkBox1632BitModeSupported.Checked ? (1 << (int)Opcodes._1632_bit_mode_supported) : 0);
            value |= (uint)(checkBox64BitModeSupported.Checked ? (1 << (int)Opcodes._64_bit_mode_supported) : 0);

            value |= (uint)(checkBoxEOSA16.Checked ? (1 << (int)Opcodes.EOSA_16) : 0);
            value |= (uint)(checkBoxEOSA32.Checked ? (1 << (int)Opcodes.EOSA_32) : 0);
            value |= (uint)(checkBoxEOSA64.Checked ? (1 << (int)Opcodes.EOSA_64) : 0);

            value |= (uint)(checkBoxEASA16.Checked ? (1 << (int)Opcodes.EASA_16) : 0);
            value |= (uint)(checkBoxEASA32.Checked ? (1 << (int)Opcodes.EASA_32) : 0);
            value |= (uint)(checkBoxEASA64.Checked ? (1 << (int)Opcodes.EASA_64) : 0);

            value |= (uint)(checkBoxForce64BitEOSA.Checked ? (1 << (int)Opcodes._In64BitModeForceEOSATo64) : 0);

            value |= (uint)(checkBoxOpcodeField_ModRM_mod3.Checked ? (1 << (int)Opcodes.AllowModRmMod3) : 0);
            value |= (uint)(checkBoxOpcodeField_ModRM_modNot3.Checked ? (1 << (int)Opcodes.AllowModRmModNot3) : 0);

            PutValueBits( ref value, (uint)int.Parse( textBoxFlagsPosition.Text ), (int)Opcodes._FIELD_POSITION_MODIFY_1, 3 );
            PutValueBits(ref value, (uint)int.Parse( textBox_opcodes_bytes.Text), (int)Opcodes._Opcode_bytes_1, 2);
            PutValueBits( ref value, (uint)int.Parse(textBoxPrimaryOpcodeIndex.Text), (int)Opcodes._Primary_Opcode_Index_1, 2);

            uint regOpcode = 0;
            regOpcode |= (uint)(checkBoxOpcodeField_ModRM_reg_0.Checked ? 0x01 : 0);
            regOpcode |= (uint)(checkBoxOpcodeField_ModRM_reg_1.Checked ? 0x02 : 0);
            regOpcode |= (uint)(checkBoxOpcodeField_ModRM_reg_2.Checked ? 0x04 : 0);
            regOpcode |= (uint)(checkBoxREX_field_R.Checked ? 0x08 : 0);

            textBoxRegOpcode.Text = "" + regOpcode;

            textBoxOpcode.Text = "0x" + value.ToString("X8");
        }

        void MapOpcodesToCheckBoxes()
        {
            string value = textBoxOpcode.Text;
            uint prefixes = (uint)Convert.ToInt32(value, 16);

            ignoreEvents = true;

            checkBoxOpcodeFieldReg.Checked = ((int)prefixes & (1 << (int)Opcodes._Reg)) != 0;
            checkBoxOpcodeFieldW.Checked = ((int)prefixes & (1 << (int)Opcodes._w)) != 0;
            checkBoxOpcodeFieldS.Checked = ((int)prefixes & (1 << (int)Opcodes._s)) != 0;
            checkBoxOpcodeFieldSreg2.Checked = ((int)prefixes & (1 << (int)Opcodes._sreg2)) != 0;
            checkBoxOpcodeFieldSreg3.Checked = ((int)prefixes & (1 << (int)Opcodes._sreg3)) != 0;
            checkBoxOpcodeFieldEEEE.Checked = ((int)prefixes & (1 << (int)Opcodes._eeee)) != 0;
            checkBoxOpcodeFieldTTTN.Checked = ((int)prefixes & (1 << (int)Opcodes._tttn)) != 0;
            checkBoxDefaultEOSA_64.Checked = ((int)prefixes & (1 << (int)Opcodes._64_Bit_EOSA_Default)) != 0;

            checkBoxREX_field_R.Checked = ((int)prefixes & (1 << (int)Opcodes._REX_FIELD_R)) != 0;
            checkBoxOpcodeField_ModRM_reg_0.Checked = ((int)prefixes & (1 << (int)Opcodes._MODRM_reg_1)) != 0;
            checkBoxOpcodeField_ModRM_reg_1.Checked = ((int)prefixes & (1 << (int)Opcodes._MODRM_reg_2)) != 0;
            checkBoxOpcodeField_ModRM_reg_2.Checked = ((int)prefixes & (1 << (int)Opcodes._MODRM_reg_3)) != 0;

            checkBoxOpcodeField_ModRM_exists.Checked = ((int)prefixes & (1 << (int)Opcodes._MOD_RM_EXISTS)) != 0;
            checkBoxOpcodeField_ModRM_reg_exists.Checked = ((int)prefixes & (1 << (int)Opcodes._MOD_RM_reg_EXISTS)) != 0;
//            checkBoxOpcodeField_ModRM_REX_R_exists.Checked = ((int)prefixes & (1 << (int)Opcodes._REX_FIELD_R_EXISTS)) != 0;
            checkBox1632BitModeSupported.Checked = ((int)prefixes & (1 << (int)Opcodes._1632_bit_mode_supported)) != 0;
            checkBox64BitModeSupported.Checked = ((int)prefixes & (1 << (int)Opcodes._64_bit_mode_supported)) != 0;

            checkBoxEOSA16.Checked = ((int)prefixes & (1 << (int)Opcodes.EOSA_16)) != 0;
            checkBoxEOSA32.Checked = ((int)prefixes & (1 << (int)Opcodes.EOSA_32)) != 0;
            checkBoxEOSA64.Checked = ((int)prefixes & (1 << (int)Opcodes.EOSA_64)) != 0;

            checkBoxEASA16.Checked = ((int)prefixes & (1 << (int)Opcodes.EASA_16)) != 0;
            checkBoxEASA32.Checked = ((int)prefixes & (1 << (int)Opcodes.EASA_32)) != 0;
            checkBoxEASA64.Checked = ((int)prefixes & (1 << (int)Opcodes.EASA_64)) != 0;

            checkBoxForce64BitEOSA.Checked = ((int)prefixes & (1 << (int)Opcodes._In64BitModeForceEOSATo64)) != 0;

            checkBoxOpcodeField_ModRM_mod3.Checked = ((int)prefixes & (1 << (int)Opcodes.AllowModRmMod3)) != 0;
            checkBoxOpcodeField_ModRM_modNot3.Checked = ((int)prefixes & (1 << (int)Opcodes.AllowModRmModNot3)) != 0;

            ulong val = GetValueBits( (uint)prefixes, (int)Opcodes._FIELD_POSITION_MODIFY_1, 3);
            textBoxFlagsPosition.Text = "" + val;
            val = GetValueBits((uint)prefixes, (int)Opcodes._Opcode_bytes_1, 2);
            textBox_opcodes_bytes.Text = "" + val;
            val = GetValueBits((uint)prefixes, (int)Opcodes._Primary_Opcode_Index_1, 2);
            textBoxPrimaryOpcodeIndex.Text = "" + val;

            ignoreEvents = false;
        }

        private void checkedChanged_Prefixes(object sender, EventArgs e)
        {
            MapCheckBoxesToPrefixes();
        }

        private void textBoxPrefixes_Validated(object sender, EventArgs e)
        {
            MapPrefixesToCheckBoxes();
        }

        private void textBoxOpcode_RightToLeftChanged(object sender, EventArgs e)
        {
            MapOpcodesToCheckBoxes();
        }

        private void checkedChanged_Opcodes(object sender, EventArgs e)
        {
            if (!ignoreEvents) {

                if (!checkBoxEOSA16.Checked && !checkBoxEOSA32.Checked && checkBoxEOSA64.Checked) {
                    checkBox1632BitModeSupported.Checked = false;
                }

                if (!checkBoxEASA16.Checked && !checkBoxEASA32.Checked && checkBoxEASA64.Checked) {
                    checkBox1632BitModeSupported.Checked = false;
                }

                MapCheckBoxesToOpcodes();
            }
        }

        void PutValueBits(ref uint value, uint val, int poz, int size)
        {
            value |= ( ( (uint)(0xFFFFFFFF >> 32 - size) & val ) << poz);
        }

        ulong GetValueBits( uint value, int pos, int size )
        {
            return ( value >> pos ) & (uint)( 0xFFFFFFFF >> 32 - size );
        }

        private void textField_Validated(object sender, EventArgs e)
        {
            MapCheckBoxesToOpcodes();
        }

        private void textBox_Opcodes_Validated(object sender, EventArgs e)
        {
            MapOpcodesToCheckBoxes();
            MapCheckBoxesToOpcodes();
        }

        private void FormCalculator_Load(object sender, EventArgs e)
        {
            textBoxOpcode.Text = "0x00000000";
            textBoxPrefixes.Text = "0x0000";
        }

        private void textBox_opcodes_bytes_TextChanged(object sender, EventArgs e) {
            try {
                int opcodeNum = Convert.ToInt32(textBox_opcodes_bytes.Text);
                textBoxPrimaryOpcodeIndex.Text = "" + (opcodeNum - 1);
            } catch (FormatException) {
                textBox_opcodes_bytes.Text = "";
                textBoxPrimaryOpcodeIndex.Text = "";
            }
        }

        private void checkBoxVEX(object sender, EventArgs e) {

            if (ignoreEvents) {
                return;
            }

            // C4/1

            byte value = 0;

            value |= (byte)(!checkBoxC4_1_R.Checked ? (1 << (byte)7) : 0);
            value |= (byte)(!checkBoxC4_1_X.Checked ? (1 << (byte)6) : 0);
            value |= (byte)(!checkBoxC4_1_B.Checked ? (1 << (byte)5) : 0);
            value |= getMMMM(comboBoxC4_1_MMMM);

            textBoxC4_1.Text = "0x" + value.ToString("X2");

            // C4/2

            value = 0;

            value |= (byte)(checkBoxC4_2_W.Checked ? (1 << (byte)7) : 0);
            value |= (byte)(getVVVV(comboBoxC4_2_VVVV) << (byte)3);
            value |= (byte)(checkBoxC4_2_L.Checked ? (1 << (byte)2) : 0);
            value |= (byte)(getPP(comboBoxC4_2_PP));

            textBoxC4_2.Text = "0x" + value.ToString("X2");

            // C5/1

            value = 0;

            value |= (byte)(!checkBoxC5_R.Checked ? (1 << (byte)7) : 0);
            value |= (byte)(getVVVV(comboBoxC5_VVVV) << (byte)3);
            value |= (byte)(checkBoxC5_L.Checked ? (1 << (byte)2) : 0);
            value |= (byte)(getPP(comboBoxC5_PP));

            textBoxC5_1.Text = "0x" + value.ToString("X2");

        }

        

        private byte getVVVV(ComboBox comboBox) {
            string reg = (string)comboBox.SelectedItem;
            if (reg == null) {
                return 0x0F;
            }
            string num = reg.Substring(3);
            byte b = (byte)(~Convert.ToByte(num));
            return (byte)( b & 0x0F );
        }

        private void setVVVV(ComboBox comboBox, byte value) {
            byte b = (byte)(0x0F & (byte)(~Convert.ToByte(value)));
            comboBox.SelectedItem = "YMM" + b;
        }

        private byte getPP(ComboBox comboBox) {
             string value = (string)comboBox.SelectedItem;
             if (value != null) {
                 switch (value) {
                     case "None":
                         return 0x00;
                     case "66":
                         return 0x01;
                     case "F3":
                         return 0x02;
                     case "F2":
                         return 0x03;
                 }
             }
            return 0;
        }

        private void setPP(ComboBox comboBox, byte value) {
            switch (value) {
                case 0x00:
                    comboBox.SelectedItem = "None";
                    break;
                case 0x01:
                    comboBox.SelectedItem = "66";
                    break;
                case 0x02:
                    comboBox.SelectedItem = "F3";
                    break;
                case 0x03:
                    comboBox.SelectedItem = "F2";
                    break;
            }
        }

        private byte getMMMM(ComboBox comboBox) {
            string value = (string)comboBox.SelectedItem;
            if (value != null) {
                switch (value) {
                    case "0F":
                        return 0x01;
                    case "0F38":
                        return 0x02;
                    case "0F3A":
                        return 0x03;
                    case "XOP 8":
                        return 0x08;
                    case "XOP 9":
                        return 0x09;
                    case "XOP 10":
                        return 0x0A;
                }
            }
            return 0;
        }

        private void setMMMM(ComboBox comboBox, byte value) {
            switch (value) {
                case 0x01:
                    comboBox.SelectedItem = "0F";
                    break;
                case 0x02:
                    comboBox.SelectedItem = "0F38";
                    break;
                case 0x03:
                    comboBox.SelectedItem = "0F3A";
                    break;
                case 0x08:
                    comboBox.SelectedItem = "XOP 8";
                    break;
                case 0x09:
                    comboBox.SelectedItem = "XOP 9";
                    break;
                case 0x0A:
                    comboBox.SelectedItem = "XOP 10";
                    break;
            }
        }

       

        private void updateC4_1(object sender, EventArgs e) {

            ignoreEvents = true;

            // C4/1

            byte prefixes = Convert.ToByte(textBoxC4_1.Text, 16);
            checkBoxC4_1_R.Checked = !(((int)prefixes & (1 << (int)7)) != 0);
            checkBoxC4_1_X.Checked = !(((int)prefixes & (1 << (int)6)) != 0);
            checkBoxC4_1_B.Checked = !(((int)prefixes & (1 << (int)5)) != 0);
            setMMMM(comboBoxC4_1_MMMM, (byte)(prefixes & 0x1F));

            ignoreEvents = false;
        }

        private void updateC4_2(object sender, EventArgs e) {

            ignoreEvents = true;

            // C4/2

            byte prefixes = Convert.ToByte(textBoxC4_2.Text, 16);
            checkBoxC4_2_W.Checked = (((int)prefixes & (1 << (int)7)) != 0);
            setVVVV(comboBoxC4_2_VVVV, (byte)((prefixes & 0x78) >> 3));
            checkBoxC4_2_L.Checked = (((int)prefixes & (1 << (int)2)) != 0);
            setPP(comboBoxC4_2_PP, (byte)(prefixes & 0x03));

            ignoreEvents = false;
        }

        private void updateC5_1(object sender, EventArgs e) {

            ignoreEvents = true;

            // C5/1

            byte prefixes = Convert.ToByte(textBoxC5_1.Text, 16);
            checkBoxC5_R.Checked = !(((int)prefixes & (1 << (int)7)) != 0);
            setVVVV(comboBoxC5_VVVV, (byte)((prefixes & 0x78) >> 3));
            checkBoxC5_L.Checked = (((int)prefixes & (1 << (int)2)) != 0);
            setPP(comboBoxC5_PP, (byte)(prefixes & 0x03));

            ignoreEvents = false;
        }

        private void clipboardCopy(object sender, EventArgs e) {
            Clipboard.SetText(textBoxC4_1.Text + ", " + textBoxC4_2.Text);
        }

        private void clipboardCopyC5(object sender, EventArgs e) {
            Clipboard.SetText(textBoxC5_1.Text);
        }

        private void buttonFromClipboard_Click(object sender, EventArgs e) {
            textBoxC5_1.Text = Clipboard.GetText();
        }

        private void buttonFromClipboardC4_Click(object sender, EventArgs e) {

            string value = Clipboard.GetText();
            string[] values = value.Split(',');

            if (values.Length > 0) {
                textBoxC4_1.Text = values[0].Trim();
            }
            if (values.Length > 1) {
                textBoxC4_2.Text = values[1].Trim();
            }
        }
    }
}