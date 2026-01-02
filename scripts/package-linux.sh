#!/usr/bin/env bash
set -euo pipefail

APP=timber
APPDIR=AppDir
ICON_SRC=graphics/player128.png
ICON_DST="$APPDIR/$APP.png"

echo "==> Cleaning old AppDir"
rm -rf "$APPDIR"
mkdir -p "$APPDIR/usr/bin"

echo "==> Copying binary"
cp "build/bin/$APP" "$APPDIR/usr/bin/"

echo "==> Copying assets"
cp -r graphics sounds fonts "$APPDIR/usr/bin/"

echo "==> Creating desktop file"
cat > "$APPDIR/$APP.desktop" <<EOF
[Desktop Entry]
Type=Application
Name=Timber
Exec=$APP
Icon=$APP
Categories=Game;
Terminal=false
EOF

echo "==> Adding icon"
if [ ! -f "$ICON_SRC" ]; then
    echo "ERROR: Icon not found: $ICON_SRC"
    exit 1
fi
cp "$ICON_SRC" "$ICON_DST"

echo "==> Downloading linuxdeploy if missing"
if [ ! -f linuxdeploy.AppImage ]; then
    curl -L -o linuxdeploy.AppImage \
      https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
    chmod +x linuxdeploy.AppImage
fi

echo "==> Building AppImage"
./linuxdeploy.AppImage \
  --appdir "$APPDIR" \
  --executable "$APPDIR/usr/bin/$APP" \
  --desktop-file "$APPDIR/$APP.desktop" \
  --icon-file "$ICON_DST" \
  --output appimage

echo "==> Done"
ls -lh *.AppImage
