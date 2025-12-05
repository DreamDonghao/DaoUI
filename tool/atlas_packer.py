import json
import os
import sys
from PIL import Image

# ========== 配置 ==========
ROOT_DIR = "example/input_images"
OUTPUT_JSON = "example/atlas_meta.json"
OUTPUT_BASE = "example/atlas/atlas"
PADDING = 2
ATLAS_WIDTH = 2048
ATLAS_HEIGHT = 2048
print("正在扫描 PNG...\n")

# 用户可自定义：atlas 在 JSON 中如何存储文件名
def make_json_atlas_path(path: str) -> str:
    # 默认仅保留文件名
    return os.path.basename(path)

# ========== 扫描所有 PNG ==========
images_to_pack = []
for root, _, files in os.walk(ROOT_DIR):
    for f in files:
        if f.lower().endswith(".png"):
            full = os.path.join(root, f)
            if f.startswith(f"{OUTPUT_BASE}_"):
                continue

            try:
                with Image.open(full) as img:
                    img.load()
                    mode, size, data = img.mode, img.size, img.tobytes()
                img = Image.frombytes(mode, size, data)

                rel = os.path.relpath(full, ROOT_DIR).replace("\\", "/")
                key = os.path.splitext(rel)[0].replace("/", "_")

                images_to_pack.append({
                    "rel": rel,
                    "key": key,
                    "img": img,
                    "w": img.width,
                    "h": img.height,
                })
                print("找到:", rel)

            except Exception as e:
                print("跳过错误图片:", full, e)

if not images_to_pack:
    print("没有 PNG 文件")
    sys.exit(1)

os.makedirs(os.path.dirname(OUTPUT_BASE), exist_ok=True)

images_to_pack.sort(key=lambda x_: x_["h"], reverse=True)

# ========== 图集打包 ==========
atlas_index = 0
cur = 0
metadata = {}

while cur < len(images_to_pack):
    atlas_name = f"{OUTPUT_BASE}_{atlas_index:04d}.png"
    atlas = Image.new("RGBA", (ATLAS_WIDTH, ATLAS_HEIGHT))
    print(f"\n--- 打包: {atlas_name} ---")

    x = y = row_h = 0
    i = cur
    packed_count = 0

    while i < len(images_to_pack):
        item = images_to_pack[i]
        w, h = item["w"], item["h"]

        new_line = (x + w > ATLAS_WIDTH)
        ny = y + row_h + PADDING if new_line else y

        if ny + h > ATLAS_HEIGHT:
            print(f"放不下，换下个图集: {item['rel']}")
            break

        if new_line:
            x = 0
            y = ny
            row_h = 0

        if x + w > ATLAS_WIDTH:
            print(f"警告：图片 {item['rel']} 宽度 {w} 超过图集宽度 {ATLAS_WIDTH}，跳过。")
            i += 1
            continue

        atlas.paste(item["img"], (x, y))
        packed_count += 1

        metadata[item["key"]] = {
            "atlas_file": make_json_atlas_path(atlas_name),   # ←← 使用自定义路径
            "atlas_id": atlas_index,
            "left": x,
            "top": y,
            "right": x + w,
            "bottom": y + h
        }

        x += w + PADDING
        row_h = max(row_h, h)

        i += 1

    if packed_count > 0:
        atlas.save(atlas_name)
        print(f"完成: {atlas_name} (包含 {packed_count} 张图片)")
    else:
        print("未打包任何图片，退出图集生成循环。")
        break

    atlas_index += 1
    cur = i

# ========== 输出 JSON ==========
with open(OUTPUT_JSON, "w", encoding="utf8") as f:
    json.dump(metadata, f, indent=2, ensure_ascii=False)

print("\n===============================")
print("图集生成完毕")
print("输出 JSON:", OUTPUT_JSON)
print(f"输出图集文件: {OUTPUT_BASE}_XXXX.png")
