namespace PR_NS_A {
   int sa = 1;

   struct PR_ST_B {
      PR_ST_B() { fb = -2; }
      int fb;
      static int sb;

      struct PR_ST_C {
         PR_ST_C() { fc = -3; }
         int fc;
         static int sc;
      };
   };

   namespace PR_NS_D {
      int sd = 4;

      struct PR_ST_E {
         PR_ST_E() { fe = -5; }
         int fe;
         static int se;

         struct PR_ST_F {
            PR_ST_F() { ff = -6; }
            int ff;
            static int sf;
         };
      };

   } // namespace D

} // namespace A

int PR_NS_A::PR_ST_B::sb                   = 2;
int PR_NS_A::PR_ST_B::PR_ST_C::sc          = 3;
int PR_NS_A::PR_NS_D::PR_ST_E::se          = 5;
int PR_NS_A::PR_NS_D::PR_ST_E::PR_ST_F::sf = 6;
