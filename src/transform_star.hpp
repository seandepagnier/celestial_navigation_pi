void frame_bias ( double &ra, double &dec );
void precess ( double jdd, double &ra, double &dec );
void nutate ( double jdd, double &ra, double &dec );
void proper_motion_parallax (double jdd, double &ra, double &dec, double dra, double ddec, double radvel, double parallax);
