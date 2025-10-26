import numpy as np
import matplotlib.pyplot as plt
from typing import List, Tuple, Dict
import pandas as pd

class PictureFuzzySet:
    """
    Lớp đại diện cho Picture Fuzzy Set (PFS)
    """
    def __init__(self, membership: List[float], non_membership: List[float], 
                 refusal: List[float], elements: List[str] = None):
        """
        Khởi tạo Picture Fuzzy Set
        
        Args:
            membership: Danh sách độ thuộc (ξ)
            non_membership: Danh sách độ không thuộc (ζ) 
            refusal: Danh sách độ từ chối (η)
            elements: Danh sách tên các phần tử
        """
        self.membership = np.array(membership)
        self.non_membership = np.array(non_membership)
        self.refusal = np.array(refusal)
        
        # Tính hesitancy (độ do dự)
        self.hesitancy = 1 - self.membership - self.non_membership - self.refusal
        
        # Kiểm tra tính hợp lệ
        self._validate()
        
        if elements is None:
            self.elements = [f"x{i+1}" for i in range(len(membership))]
        else:
            self.elements = elements
    
    def _validate(self):
        """Kiểm tra tính hợp lệ của PFS"""
        # Kiểm tra điều kiện 0 ≤ ξ, ζ, η ≤ 1
        if not all(0 <= val <= 1 for val in self.membership):
            raise ValueError("Membership values must be in [0, 1]")
        if not all(0 <= val <= 1 for val in self.non_membership):
            raise ValueError("Non-membership values must be in [0, 1]")
        if not all(0 <= val <= 1 for val in self.refusal):
            raise ValueError("Refusal values must be in [0, 1]")
        
        # Kiểm tra điều kiện ξ + ζ + η ≤ 1
        sum_values = self.membership + self.non_membership + self.refusal
        if not all(val <= 1.001 for val in sum_values):  # Cho phép sai số làm tròn nhỏ
            raise ValueError("Sum of membership, non-membership, and refusal must not exceed 1")
        
        # Sửa lỗi hesitancy âm do sai số làm tròn
        self.hesitancy = np.maximum(0, self.hesitancy)
        
        # Kiểm tra hesitancy không âm
        if not all(val >= -0.001 for val in self.hesitancy):  # Cho phép sai số làm tròn nhỏ
            raise ValueError("Hesitancy values must be non-negative")
    
    def __str__(self):
        """Hiển thị PFS"""
        result = "Picture Fuzzy Set:\n"
        for i, elem in enumerate(self.elements):
            result += f"{elem}: (ξ={self.membership[i]:.3f}, ζ={self.non_membership[i]:.3f}, "
            result += f"η={self.refusal[i]:.3f}, θ={self.hesitancy[i]:.3f})\n"
        return result


def pfhd_distance(pfs1: PictureFuzzySet, pfs2: PictureFuzzySet) -> float:
    """
    Tính Picture Fuzzy Hellinger Distance (PFHD) giữa hai PFS
    
    Công thức: D_PFHD(P,Q) = (1/√2) * √[(1/n) * Σ[(√ξP - √ξQ)² + (√ζP - √ζQ)² + (√ηP - √ηQ)² + (√θP - √θQ)²]]
    
    Args:
        pfs1: Picture Fuzzy Set thứ nhất
        pfs2: Picture Fuzzy Set thứ hai
    
    Returns:
        float: Giá trị PFHD distance
    """
    if len(pfs1.membership) != len(pfs2.membership):
        raise ValueError("Two PFS must have the same number of elements")
    
    n = len(pfs1.membership)
    
    # Đảm bảo tất cả giá trị không âm trước khi lấy căn
    membership1 = np.maximum(0, pfs1.membership)
    membership2 = np.maximum(0, pfs2.membership)
    non_membership1 = np.maximum(0, pfs1.non_membership)
    non_membership2 = np.maximum(0, pfs2.non_membership)
    refusal1 = np.maximum(0, pfs1.refusal)
    refusal2 = np.maximum(0, pfs2.refusal)
    hesitancy1 = np.maximum(0, pfs1.hesitancy)
    hesitancy2 = np.maximum(0, pfs2.hesitancy)
    
    # Tính các thành phần của công thức
    membership_diff = (np.sqrt(membership1) - np.sqrt(membership2)) ** 2
    non_membership_diff = (np.sqrt(non_membership1) - np.sqrt(non_membership2)) ** 2
    refusal_diff = (np.sqrt(refusal1) - np.sqrt(refusal2)) ** 2
    hesitancy_diff = (np.sqrt(hesitancy1) - np.sqrt(hesitancy2)) ** 2
    
    # Tính tổng
    total_sum = np.sum(membership_diff + non_membership_diff + refusal_diff + hesitancy_diff)
    
    # Áp dụng công thức PFHD
    pfhd = (1 / np.sqrt(2)) * np.sqrt((1 / n) * total_sum)
    
    return pfhd


def hamming_distance(pfs1: PictureFuzzySet, pfs2: PictureFuzzySet) -> float:
    """Tính Hamming distance giữa hai PFS để so sánh"""
    if len(pfs1.membership) != len(pfs2.membership):
        raise ValueError("Two PFS must have the same number of elements")
    
    n = len(pfs1.membership)
    
    membership_diff = np.abs(pfs1.membership - pfs2.membership)
    non_membership_diff = np.abs(pfs1.non_membership - pfs2.non_membership)
    refusal_diff = np.abs(pfs1.refusal - pfs2.refusal)
    hesitancy_diff = np.abs(pfs1.hesitancy - pfs2.hesitancy)
    
    hamming = (1 / (4 * n)) * np.sum(membership_diff + non_membership_diff + refusal_diff + hesitancy_diff)
    
    return hamming


def euclidean_distance(pfs1: PictureFuzzySet, pfs2: PictureFuzzySet) -> float:
    """Tính Euclidean distance giữa hai PFS để so sánh"""
    if len(pfs1.membership) != len(pfs2.membership):
        raise ValueError("Two PFS must have the same number of elements")
    
    n = len(pfs1.membership)
    
    membership_diff = (pfs1.membership - pfs2.membership) ** 2
    non_membership_diff = (pfs1.non_membership - pfs2.non_membership) ** 2
    refusal_diff = (pfs1.refusal - pfs2.refusal) ** 2
    hesitancy_diff = (pfs1.hesitancy - pfs2.hesitancy) ** 2
    
    euclidean = np.sqrt((1 / (4 * n)) * np.sum(membership_diff + non_membership_diff + refusal_diff + hesitancy_diff))
    
    return euclidean


def compare_distance_measures(pfs_pairs: List[Tuple[PictureFuzzySet, PictureFuzzySet]], 
                            pair_names: List[str] = None) -> pd.DataFrame:
    """
    So sánh các độ đo khoảng cách khác nhau
    """
    if pair_names is None:
        pair_names = [f"Pair {i+1}" for i in range(len(pfs_pairs))]
    
    results = []
    
    for i, (pfs1, pfs2) in enumerate(pfs_pairs):
        pfhd = pfhd_distance(pfs1, pfs2)
        hamming = hamming_distance(pfs1, pfs2)
        euclidean = euclidean_distance(pfs1, pfs2)
        
        results.append({
            'Pair': pair_names[i],
            'PFHD': pfhd,
            'Hamming': hamming,
            'Euclidean': euclidean
        })
    
    return pd.DataFrame(results)


def visualize_pfs(pfs: PictureFuzzySet, title: str = "Picture Fuzzy Set"):
    """Trực quan hóa PFS"""
    fig, ax = plt.subplots(figsize=(10, 6))
    
    x = range(len(pfs.elements))
    width = 0.2
    
    ax.bar([i - 1.5*width for i in x], pfs.membership, width, label='Membership (ξ)', alpha=0.8)
    ax.bar([i - 0.5*width for i in x], pfs.non_membership, width, label='Non-membership (ζ)', alpha=0.8)
    ax.bar([i + 0.5*width for i in x], pfs.refusal, width, label='Refusal (η)', alpha=0.8)
    ax.bar([i + 1.5*width for i in x], pfs.hesitancy, width, label='Hesitancy (θ)', alpha=0.8)
    
    ax.set_xlabel('Elements')
    ax.set_ylabel('Values')
    ax.set_title(title)
    ax.set_xticks(x)
    ax.set_xticklabels(pfs.elements)
    ax.legend()
    ax.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.show()



if __name__ == "__main__":
    print("=== PICTURE FUZZY HELLINGER DISTANCE CALCULATOR ===\n")
    
    # Tạo hai PFS mẫu
    print("1. Tạo hai Picture Fuzzy Sets mẫu:")
    
    # PFS 1
    pfs1 = PictureFuzzySet(
        membership=[0.6, 0.7, 0.5, 0.8],
        non_membership=[0.2, 0.1, 0.3, 0.1],
        refusal=[0.1, 0.2, 0.1, 0.0],
        elements=['A', 'B', 'C', 'D']
    )
    print("PFS 1:")
    print(pfs1)
    
    # PFS 2
    pfs2 = PictureFuzzySet(
        membership=[0.5, 0.8, 0.6, 0.7],
        non_membership=[0.3, 0.1, 0.2, 0.2],
        refusal=[0.1, 0.1, 0.2, 0.1],
        elements=['A', 'B', 'C', 'D']
    )
    print("PFS 2:")
    print(pfs2)
    
    # Tính các độ đo khoảng cách
    print("\n2. Tính toán các độ đo khoảng cách:")
    pfhd = pfhd_distance(pfs1, pfs2)
    hamming = hamming_distance(pfs1, pfs2)
    euclidean = euclidean_distance(pfs1, pfs2)
    
    print(f"PFHD Distance: {pfhd:.6f}")
    print(f"Hamming Distance: {hamming:.6f}")
    print(f"Euclidean Distance: {euclidean:.6f}")
    
    # Tạo thêm một số PFS để so sánh (cùng số phần tử)
    print("\n3. So sánh với nhiều cặp PFS:")
    
    pfs3 = PictureFuzzySet([0.9, 0.8, 0.7, 0.6], [0.05, 0.1, 0.2, 0.3], [0.05, 0.1, 0.1, 0.1])
    pfs4 = PictureFuzzySet([0.1, 0.2, 0.3, 0.4], [0.8, 0.7, 0.6, 0.5], [0.1, 0.1, 0.1, 0.1])
    
    pairs = [(pfs1, pfs2), (pfs3, pfs4), (pfs1, pfs3)]
    comparison_df = compare_distance_measures(pairs, ['Similar PFS', 'Opposite PFS', 'Mixed PFS'])
    
    print(comparison_df.to_string(index=False))

# Ví dụ phản trực quan trong bài báo 2023 Iranian Journal of Fuzzy Systems
#A picture fuzzy distance measure and its application to pattern recognition problems

    print("\n2. Tính toán các độ đo khoảng cách bai bao 2023: Ex4.3")
    a1 = PictureFuzzySet([0.3], [0.0], [0.7])
    b1 = PictureFuzzySet([0.4], [0.0], [0.6])
    # Tính các độ đo khoảng cách
    pfhd = pfhd_distance(a1, b1)
    #hamming = hamming_distance(a1, b1)
    #euclidean = euclidean_distance(a1, b1)
    print(f"PFHD Distance a1, b1: {pfhd:.6f}")
    #print(f"Hamming Distance a1, b1: {hamming:.6f}")
    #print(f"Euclidean Distance a1, b1: {euclidean:.6f}")

    a2 = PictureFuzzySet([0.1], [0.4], [0.5])
    b2 = PictureFuzzySet([0.2], [0.5], [0.3])
    # Tính các độ đo khoảng cách
    pfhd = pfhd_distance(a2, b2)
    #hamming = hamming_distance(a2, b2)
    #euclidean = euclidean_distance(a2, b2)
    print(f"PFHD Distance a2, b2: {pfhd:.6f}")
    #print(f"Hamming Distance a2, b2: {hamming:.6f}")
    #print(f"Euclidean Distance a2, b2: {euclidean:.6f}")
    #case 3
    a3 = PictureFuzzySet([0.4], [0.0], [0.6])
    b3 = PictureFuzzySet([0.0], [0.0], [0.0])
    pfhd = pfhd_distance(a3, b3)
    print(f"PFHD Distance a3, b3: {pfhd:.6f}")
    #case 4
    a4 = PictureFuzzySet([0.0], [0.0], [0.5])
    b4 = PictureFuzzySet([0.0], [0.0], [0.0])
    pfhd = pfhd_distance(a4, b4)
    print(f"PFHD Distance a4, b4: {pfhd:.6f}")
   #case 5
    a5 = PictureFuzzySet([0.3], [0.0], [0.7])
    b5 = PictureFuzzySet([0.2], [0.0], [0.8])
    pfhd = pfhd_distance(a5, b5)
    print(f"PFHD Distance a5, b5: {pfhd:.6f}")
    #case 6
    a6 = PictureFuzzySet([0.3], [0.0], [0.7])
    b6 = PictureFuzzySet([0.4], [0.0], [0.6])
    pfhd = pfhd_distance(a6, b6)
    print(f"PFHD Distance a6, b6: {pfhd:.6f}")

# Ví dụ phản trực quan trong bài báo 2023 Iranian Journal of Fuzzy Systems
#A picture fuzzy distance measure and its application to pattern recognition problems
    print("\n3. Tính toán các độ đo khoảng cách bai bao 2023: Ex4.4")
    #case 1
    a1 = PictureFuzzySet([0.6], [0.27], [0.1])
    b1 = PictureFuzzySet([0.28], [0.55], [0.1])
    pfhd = pfhd_distance(a1, b1)
    print(f"PFHD Distance a1, b1: {pfhd:.6f}")
    #case 2
    a2 = PictureFuzzySet([0.0], [0.87], [0.1])
    b2 = PictureFuzzySet([0.28], [0.55], [0.1])
    pfhd = pfhd_distance(a2, b2)
    print(f"PFHD Distance a2, b2: {pfhd:.6f}")
    #case 3
    a3 = PictureFuzzySet([0.6], [0.4], [0.0])
    b3 = PictureFuzzySet([0.0], [0.0], [0.0])
    pfhd = pfhd_distance(a3, b3)
    print(f"PFHD Distance a3, b3: {pfhd:.6f}")
    #case 4
    a4 = PictureFuzzySet([0.5], [0.5], [0.0])
    b4 = PictureFuzzySet([0.0], [0.0], [0.0])
    pfhd = pfhd_distance(a4, b4)
    print(f"PFHD Distance a4, b4: {pfhd:.6f}")  
