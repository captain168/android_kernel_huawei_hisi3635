cmd_scripts/mod/empty.o :=   /home/kevin/aarch64-linux-android-4.9/bin/aarch64-linux-android-gcc -Wp,-MD,scripts/mod/.empty.o.d  -nostdinc -isystem /home/kevin/aarch64-linux-android-4.9/bin/../lib/gcc/aarch64-linux-android/4.9.x/include -I/home/kevin/Downloads/mates/11/kernel/kernel/arch/arm64/include -Iarch/arm64/include/generated  -Iinclude -I/home/kevin/Downloads/mates/11/kernel/kernel/arch/arm64/include/uapi -Iarch/arm64/include/generated/uapi -I/home/kevin/Downloads/mates/11/kernel/kernel/include/uapi -Iinclude/generated/uapi -include /home/kevin/Downloads/mates/11/kernel/kernel/include/linux/kconfig.h -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/ -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/vendor/hisi/config/product/hi3635_udp/config -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/vendor/hisi/platform/hi3630 -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/vendor/hisi/platform/hi3630/soc -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/vendor/hisi/config/product/hi3635_udp/include_gu -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/vendor/hisi/config/nvim/include/gu -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/vendor/hisi/../../external/efipartition -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/vendor/hisi/include/drv -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/vendor/hisi/include/drv/acore -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/vendor/hisi/include/drv/common -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/vendor/hisi/include/nv/tl/drv -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/vendor/hisi/include/nv/tl/oam -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/vendor/hisi/include/nv/tl/lps -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/vendor/hisi/include/phy/lphy -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/vendor/hisi/audiodsp/custom/hi6402_hifi/include/med -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/vendor/hisi/include/taf -I/home/kevin/Downloads/mates/11/kernel/kernel/../kernel/drivers/vendor/hisi/modem/drv/common/include -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Wimplicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -DFEATURE_ON=1 -DFEATURE_OFF=0 -DFEATURE_UE_MODE_CDMA=FEATURE_OFF -DBSP_CORE_APP -DBSP_COMPILE_ALLY -O2 -g -mgeneral-regs-only -fno-pic -Wframe-larger-than=2048 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack    -DBSP_CORE_APP -DBSP_COMPILE_ALLY -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(empty)"  -D"KBUILD_MODNAME=KBUILD_STR(empty)" -c -o scripts/mod/empty.o scripts/mod/empty.c

source_scripts/mod/empty.o := scripts/mod/empty.c

deps_scripts/mod/empty.o := \

scripts/mod/empty.o: $(deps_scripts/mod/empty.o)

$(deps_scripts/mod/empty.o):