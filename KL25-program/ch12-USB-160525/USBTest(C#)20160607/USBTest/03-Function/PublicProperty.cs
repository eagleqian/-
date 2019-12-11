using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Function
{
    class PublicProperty
    {
        // USB参数设置
        public const int myPID = 0xA50F;
        public const int myVID = 0x15A2;
        public enum eCmd : byte
        {
            cmdNULL         = 0x00,
            cmdOUTTESTDATA  = 0X01,
            cmdINTESTDATA   = 0X02,
            cmdMAX
        };
        public const int FRAMEHEADLENGTH = 1;
    }
}
