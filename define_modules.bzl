load("//build/bazel_common_rules/dist:dist.bzl", "copy_to_dist_dir")
load("//build/kernel/kleaf:kernel.bzl", "ddk_module")

def define_modules(target, variant):
    kernel_build_variant = "{}_{}".format(target, variant)
    include_base = "../../../{}".format(native.package_name())

    #The below will take care of the defconfig
    include_defconfig = ":{}_defconfig".format(variant)
    print(kernel_build_variant)
    print(include_base)
    print(include_defconfig)

    mod_list = []

    ddk_module(
        name = "{}_sch".format(kernel_build_variant),
        out = "rmnet_sch.ko",
        srcs = [
            "sch/rmnet_sch_main.c",
        ],
	kernel_build = "//msm-kernel:{}-defconfig".format(kernel_build_variant),
	copts = ["-Wno-misleading-indentation"],
        deps = [
            "//msm-kernel:all_headers",
	    ":rmnet_ext_headers",
        ],
    )
    mod_list.append("{}_sch".format(kernel_build_variant))

    copy_to_dist_dir(
        name = "{}-defconfig_datarmnet-ext_dist".format(kernel_build_variant),
        data = mod_list,
        dist_dir = "out/target/product/{}/dlkm/lib/modules/".format(target),
        flat = True,
        wipe_dist_dir = False,
        allow_duplicate_filenames = False,
        mode_overrides = {"**/*": "644"},
        log = "info",
    )
