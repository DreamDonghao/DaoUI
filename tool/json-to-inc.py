import json

with open("example/atlas_meta.json", "r", encoding="utf-8") as f:
    data = json.load(f)

def to_enum_name(s: str) -> str:
    return s.replace(".", "_").replace("-", "_")

# textures.inc —— 全部放一行
textures = ",".join(data.keys())
with open("example/inc/textures.inc", "w", encoding="utf-8") as f:
    f.write(textures + ',')

# texture_datas.inc —— 全部放一行，无换行
region_entries = []
for name, v in data.items():
    region_entries.append(
        f'{{"{v["atlas_file"]}",{v["atlas_id"]},{v["left"]/2048},{v["top"]/2048},{v["right"]/2048},{v["bottom"]/2048}}}'
    )

with open("example/inc/texture_datas.inc", "w", encoding="utf-8") as f:
    f.write(",".join(region_entries))

print("inc")
