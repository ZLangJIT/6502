{stdenv, lib, cmake, pwd, dtc}: let
in
stdenv.mkDerivation {
  name = "6502";

  src = "${pwd}";

  nativeBuildInputs = [ cmake ];

  meta = {
    description = "6502";
    homepage = https://github.com/ZLangJIT/6502;
    license = lib.licenses.bsd3;
    maintainers = [ "ZLangJIT" ];
  };
}
