Name:       capi-bps-bp-tizen
Summary:    BestPractice Tizen native API
Version:    0.0.1
Release:    0
Group:      System/API
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1001:     capi-bps-bp-tizen.manifest
BuildRequires:  cmake
BuildRequires:  tidl
BuildRequires:  pkgconfig(rpc-port)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(bundle)
BuildRequires:  pkgconfig(eina)
BuildRequires:  pkgconfig(ecore)
#BuildRequires:  pkgconfig(gmock)
%if 0%{?gcov:1}
BuildRequires:  lcov
BuildRequires:  zip
%endif

%description
An best practice tizen native library in Tizen C API

%package devel
Summary:  An best practice tizen native library in Tizen C API (Development)
Group:    System/API
Requires: %{name} = %{version}-%{release}

%description devel
An best practice tizen native library in Tizen C API (Development) package.

#################################################
# capi-bps-bp-tizen-unittests
#################################################
%package -n capi-bps-bp-tizen-unittests
Summary:    GTest for bp-tizen API
Group:      Development/Libraries
Requires:   %{name}

%description -n capi-bps-bp-tizen-unittests
GTest for bp-tizen API

#################################################
# capi-bps-bp-tizen-gcov
#################################################
%if 0%{?gcov:1}
%package gcov
Summary:    Best practice tizen native API(gcov)
Group:      Application Framework/Testing

%description gcov
Best practice tizen gcov objects
%endif

%prep
%setup -q
cp %{SOURCE1001} .
tidlc -p -l C -i ./src/tidl/remote_service.tidl -o remote_service_proxy
mv remote_service_proxy.c src/
mv remote_service_proxy.h src/ 
tidlc -s -l C -i ./src/tidl/stub_service.tidl -o stub_service_stub
mv stub_service_stub.c src/ 
mv stub_service_stub.h src/

%build
%if 0%{?gcov:1}
export CFLAGS+=" -fprofile-arcs -ftest-coverage"
export CXXFLAGS+=" -fprofile-arcs -ftest-coverage"
export FFLAGS+=" -fprofile-arcs -ftest-coverage"
export LDFLAGS+=" -lgcov"
%endif

MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER}
%__make %{?jobs:-j%jobs}

%if 0%{?gcov:1}
mkdir -p gcov-obj
find . -name '*.gcno' -exec cp '{}' gcov-obj ';'
%endif

%check
ctest --output-on-failure %{?_smp_mflags}
%if 0%{?gcov:1}
lcov -c --ignore-errors graph --no-external -q -d . -o bp-tizen.info
genhtml bp-tizen.info -o bp-tizen.out
zip -r bp-tizen.zip bp-tizen.out bp-tizen.info
install -m 0644 bp-tizen.zip %{buildroot}%{_datadir}/gcov/
%endif

%install
rm -rf %{buildroot}
%make_install

%if 0%{?gcov:1}
mkdir -p %{buildroot}%{_datadir}/gcov/obj
install -m 0644 gcov-obj/* %{buildroot}%{_datadir}/gcov/obj
%endif

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig
#rm -f src/remote_service_proxy.c
#rm -f src/remote_service_stub.c
#rm -f src/remote_service_proxy.h
#rm -f src/remote_service_stub.h

#%post -n capi-bps-bp-tizen-unittests
#%if 0%{?gcov:1}
#%{_bindir}/bp-tizen_unittests
#%endif

%files
%manifest %{name}.manifest
%{_libdir}/libcapi-bps-bp-tizen.so.*
%license LICENSE

%files devel
%manifest %{name}.manifest
%{_includedir}/bp-tizen/bp_tizen_common.h
%{_libdir}/pkgconfig/capi-bps-bp-tizen.pc
%{_libdir}/libcapi-bps-bp-tizen.so

#################################################
# capi-bps-bp-tizen-unittests
#################################################
#%files -n capi-bps-bp-tizen-unittests
#%{_bindir}/bp-tizen_unittests

#################################################
# capi-bps-bp-tizen-gcov
#################################################
%if 0%{?gcov:1}
%files gcov
%{_datadir}/gcov/*
%endif
