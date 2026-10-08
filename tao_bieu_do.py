import csv
import re
import sys
from pathlib import Path

import matplotlib.pyplot as plt


# Dat ket_qua.csv cung thu muc voi file Python nay.
# Hoac chay: python tao_bieu_do.py "duong_dan/ket_qua.csv"
thu_muc = Path(__file__).resolve().parent
file_csv = Path(sys.argv[1]) if len(sys.argv) > 1 else thu_muc / "ket_qua.csv"

ten_cot = [
    "QuickSort (ms)",
    "HeapSort (ms)",
    "MergeSort (ms)",
    "sort C++ (ms)",
]
ten_thuat_toan = ["Quicksort", "Heapsort", "Mergesort", "sort (C++)"]
mau = ["#5B9BD5", "#ED7D31", "#A5A5A5", "#FFC000"]

nhan = []
thoi_gian = [[], [], [], []]

try:
    with open(file_csv, encoding="utf-8-sig", newline="") as f:
        # Ho tro CSV dung dau phay hoac dau cham phay.
        dong_dau = f.readline()
        dau_ngan = ";" if ";" in dong_dau else ","
        f.seek(0)
        bang = csv.DictReader(f, delimiter=dau_ngan)

        if not bang.fieldnames or not all(
            cot in bang.fieldnames for cot in ["Du lieu"] + ten_cot
        ):
            raise ValueError("Ten cot CSV khong dung voi file ket_qua.csv da tao.")

        for dong in bang:
            ten = dong["Du lieu"].strip()
            if not ten or ten.lower() in ["trung binh", "trung bình"]:
                continue

            # Chuyen data1.txt thanh nhan 1, data2.txt thanh nhan 2...
            so = re.fullmatch(r"data(\d+)\.txt", ten, re.IGNORECASE)
            nhan.append(str(int(so.group(1))) if so else ten)

            for i in range(4):
                gia_tri = float(dong[ten_cot[i]].strip().replace(",", "."))
                if not (0 <= gia_tri < float("inf")):
                    raise ValueError("Thoi gian phai la so huu han khong am.")
                thoi_gian[i].append(gia_tri)

    if not nhan:
        raise ValueError("File CSV khong co dong du lieu de ve.")
except (OSError, ValueError, TypeError, AttributeError) as loi:
    raise SystemExit(f"Khong doc duoc du lieu: {loi}")


plt.rcParams["font.family"] = "Arial"
plt.rcParams["font.size"] = 11

# Tang chieu ngang khi ve nhieu day de cac cot khong bi chen nhau.
chieu_rong = max(9, len(nhan) * 1.8)
fig, ax = plt.subplots(figsize=(chieu_rong, 5.5))
fig.patch.set_facecolor("white")

rong_cot = 0.18
cao_nhat = max(max(day) for day in thoi_gian)
gioi_han = cao_nhat * 1.15 if cao_nhat > 0 else 1

for i in range(4):
    vi_tri = [x + (i - 1.5) * rong_cot for x in range(len(nhan))]
    cac_cot = ax.bar(
        vi_tri,
        thoi_gian[i],
        width=rong_cot,
        color=mau[i],
        label=ten_thuat_toan[i],
    )

    for cot in cac_cot:
        cao = cot.get_height()
        # Cot thap thi dat so phia tren, cot cao thi dat so o giua.
        if cao < gioi_han * 0.10:
            y = cao + gioi_han * 0.015
            can_doc = "bottom"
        else:
            y = cao / 2
            can_doc = "center"

        ax.text(
            cot.get_x() + cot.get_width() / 2,
            y,
            f"{cao:.2f}",
            ha="center",
            va=can_doc,
            fontsize=8 if len(nhan) > 5 else 10,
            color="#333333",
        )

ax.set_title("Kết quả thử nghiệm trên bộ dữ liệu", fontsize=19, pad=22, color="#595959")
ax.set_ylabel("Thời gian thực hiện (ms)", fontsize=12, color="#595959")
ax.set_xlabel("Dãy dữ liệu", fontsize=12, labelpad=10, color="#595959")
ax.set_xticks(range(len(nhan)))
ax.set_xticklabels(nhan)
ax.set_ylim(0, gioi_han)

ax.set_axisbelow(True)
ax.grid(axis="y", color="#D9D9D9", linewidth=0.8)
ax.tick_params(axis="both", length=0, pad=10, colors="#595959")
for canh in ax.spines.values():
    canh.set_visible(False)

ax.legend(
    loc="center left",
    bbox_to_anchor=(1.02, 0.5),
    frameon=False,
    labelspacing=1.2,
    handlelength=0.8,
)

fig.tight_layout()
file_png = file_csv.resolve().parent / "bieu_do_sap_xep.png"
file_pdf = file_csv.resolve().parent / "bieu_do_sap_xep.pdf"
fig.savefig(file_png, dpi=300, bbox_inches="tight", facecolor="white")
fig.savefig(file_pdf, bbox_inches="tight", facecolor="white")
print(f"Da luu anh: {file_png}")
print(f"Da luu PDF: {file_pdf}")
plt.show()
