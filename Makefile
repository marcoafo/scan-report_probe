include $(TOPDIR)/rules.mk

# name of package
# version number of the sources you're using
# how many times you've released a package based on the above version number
PKG_NAME:=scanReport_probe
PKG_VERSION:=1.0
PKG_RELEASE:=1
PKG_LICENSE:=MIT

# sources will be unpacked into this directory (you shouldn't need to change this)
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

#needed 
include $(INCLUDE_DIR)/package.mk


# Metadata; information about what the package is for the ipkg listings
# to keep things simple, a number of fields have been left at their defaults
# and are not shown here.
define Package/scanReport_probe
	SECTION:=utils
	CATEGORY:=Utilities
	TITLE:=scanReport_probe
	URL:=https://github.com/luigiDB/scan-report_probe
	TITLE:=Scan in monitor mode probe over wifi channel with periodic report to a server through http post.
	MAINTAINER:=Please refer to github repository page
endef

define Package/scanReport_probe/description
	This is the best tool ever. 
	Scan probe over wifi and at regualar interval send results via http post.
endef


define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef


CONFIGURE_VARS+= \
	CC="$(TOOLCHAIN_DIR)/bin/$(TARGET_CC)"


define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)/scanReport_probe $(TARGET_CONFIGURE_OPTS)
endef
	
# We'll use the OpenWrt defaults to configure and compile the package. Otherwise we'd need to define
# Build/Configure - commands to invoke a configure (or similar) script
# Build/Compile - commands used to run make or otherwise build the source

define Package/scanReport_probe/install
	# Now that we have the source compiled (magic huh?) we need to copy files out of the source
	# directory and into our ipkg file. These are shell commands, so make sure you start the lines
	# with a TAB. $(1) here represents the root filesystem on the router.
	# INSTALL_DIR, INSTALL_BIN, INSTALL_DATA are used for creating a directory, copying an executable, 
	# or a data file. +x is set on the target file for INSTALL_BIN, independent of it's mode on the host.

	# make a directory for the config
	$(INSTALL_DIR) $(1)/etc/scanReport_probe/
	
	# copy the config
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/scanReport_probe.conf $(1)/etc/scanReport_probe
	
	# make a directory for some random data files required by scanReport_probe
	$(INSTALL_DIR) $(1)/usr/share/scanReport_probe
	
	# copy the data files
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/data/* $(1)/usr/share/scanReport_probe
	
	#make directory bin
	$(INSTALL_DIR) $(1)/bin
	
	# copy the binary
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scanReport_probe/a $(1)/bin
	
	#make the directory init.d in case isn't present
	$(INSTALL_DIR) $(1)/etc/init.d
	
	#copy script to init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/runScript/scanReportProbe $(1)/etc/init.d	
endef


#runned post installation call the enable on the service
define Package/scanReport_probe/postinst
	#!/bin/sh
	# check if we are on real system
	if [ -z "$${IPKG_INSTROOT}" ]; then
		echo "Enabling rc.d symlink for scanReportProbe"
		/etc/init.d/scanReportProbe enable
	fi
	exit 0
endef


#runned pre uninstallation call the disable on the service
define Package/scanReport_probe/prerm
	#!/bin/sh
	# check if we are on real system
	if [ -z "$${IPKG_INSTROOT}" ]; then
		echo "Removing rc.d symlink for scanReportProbe"
		/etc/init.d/scanReportProbe disable
	fi
	exit 0
endef

$(eval $(call BuildPackage,scanReport_probe))

