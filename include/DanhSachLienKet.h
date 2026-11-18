#ifndef DANHSACHLIENKET_H_INCLUDED_
#define DANHSACHLIENKET_H_INCLUDED_

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class DanhSachLienKet
{
public:
	DanhSachLienKet();
	DanhSachLienKet(const DanhSachLienKet<T>& danhSachNguon);
	~DanhSachLienKet();
	DanhSachLienKet<T>& operator=(const DanhSachLienKet<T>& danhSachNguon);

	void themCuoi(const T& duLieu);
	void xoaTatCa();
	std::size_t layKichThuoc() const;
	bool laRong() const;
	const T& layTai(const std::size_t uiViTri) const;

	template <typename TieuChi>
	T* timDauTien(TieuChi tieuChi);

	template <typename TieuChi>
	const T* timDauTien(TieuChi tieuChi) const;

	template <typename TieuChi>
	bool xoaDauTien(TieuChi tieuChi);

	template <typename HanhDong>
	void duyet(HanhDong hanhDong) const;

private:
	struct NUT
	{
		T DuLieu;
		NUT* TiepTheo;
		explicit NUT(const T& duLieu) : DuLieu(duLieu), TiepTheo(nullptr)
		{
			//TODO: Empty Method
		}
	};

	void saoChep(const DanhSachLienKet<T>& danhSachNguon);
	NUT* _pDau;
	NUT* _pCuoi;
	std::size_t _uiKichThuoc;
};

/**********************************************************
* @Description Khoi tao danh sach lien ket rong.
*
* @return Khong co gia tri tra ve.
* @attention Ket qua: Dau/cuoi bang nullptr, kich thuoc bang 0.
* @attention Su dung: Khoi tao cac thuoc tinh noi bo.
**********************************************************/
template <typename T>
DanhSachLienKet<T>::DanhSachLienKet()
	: _pDau(nullptr),
	  _pCuoi(nullptr),
	  _uiKichThuoc(0)
{
	//TODO: Empty Method
}

/**********************************************************
* @Description Khoi tao danh sach bang ban sao doc lap cua danhSachNguon.
*
* @return Khong co gia tri tra ve.
* @attention Dieu kien dau: danhSachNguon la danh sach hop le; T co the sao chep.
* @attention Ket qua: Danh sach moi co cac phan tu tuong ung; neu sao chep loi, giai phong node da tao va nem lai ngoai le.
* @attention Su dung: saoChep(), xoaTatCa().
**********************************************************/
template <typename T>
DanhSachLienKet<T>::DanhSachLienKet(const DanhSachLienKet<T>& danhSachNguon)
	: _pDau(nullptr),
	  _pCuoi(nullptr),
	  _uiKichThuoc(0)
{
	try
	{
		this->saoChep(danhSachNguon);
	}
	catch (...)
	{
		this->xoaTatCa();
		throw;
	}
}

/**********************************************************
* @Description Huy danh sach va giai phong cac node.
*
* @return Khong co gia tri tra ve.
* @attention Dieu kien dau: Doi tuong duoc khoi tao hop le.
* @attention Ket qua: Cac node do danh sach so huu duoc giai phong.
* @attention Su dung: xoaTatCa().
**********************************************************/
template <typename T>
DanhSachLienKet<T>::~DanhSachLienKet()
{
	this->xoaTatCa();
}

/**********************************************************
* @Description Gan noi dung tu danhSachNguon bang copy-and-swap.
*
* @return Tham chieu den danh sach dich.
* @attention Dieu kien dau: T co the sao chep.
* @attention Ket qua: Thanh cong: noi dung giong danhSachNguon; neu sao chep nem ngoai le, danh sach dich giu nguyen.
* @attention Su dung: Copy constructor, std::swap(), destructor.
**********************************************************/
template <typename T>
DanhSachLienKet<T>& DanhSachLienKet<T>::operator=(const DanhSachLienKet<T>& danhSachNguon)
{
	if (this != &danhSachNguon)
	{
		DanhSachLienKet<T> danhSachTam(danhSachNguon);

		std::swap(this->_pDau, danhSachTam._pDau);
		std::swap(this->_pCuoi, danhSachTam._pCuoi);
		std::swap(this->_uiKichThuoc, danhSachTam._uiKichThuoc);
	}

	return *this;
}

/**********************************************************
* @Description Them ban sao duLieu vao cuoi danh sach.
*
* @return Khong co gia tri tra ve.
* @attention Dieu kien dau: T co the sao chep.
* @attention Ket qua: Thanh cong: kich thuoc tang 1, thu tu phan tu cu duoc giu nguyen.
* @attention Su dung: new NUT(duLieu).
**********************************************************/
template <typename T>
void DanhSachLienKet<T>::themCuoi(const T& duLieu)
{
	NUT* pNutMoi = new NUT(duLieu);

	if (this->_pCuoi == nullptr)
	{
		this->_pDau = pNutMoi;
	}
	else
	{
		this->_pCuoi->TiepTheo = pNutMoi;
	}

	this->_pCuoi = pNutMoi;
	++this->_uiKichThuoc;
}

/**********************************************************
* @Description Xoa toan bo node trong danh sach.
*
* @return Khong co gia tri tra ve.
* @attention Dieu kien dau: Danh sach hop le.
* @attention Ket qua: Danh sach rong; dau/cuoi bang nullptr va kich thuoc bang 0.
* @attention Su dung: delete tung NUT.
**********************************************************/
template <typename T>
void DanhSachLienKet<T>::xoaTatCa()
{
	NUT* pHienTai = this->_pDau;

	while (pHienTai != nullptr)
	{
		NUT* pTiepTheo = pHienTai->TiepTheo;
		delete pHienTai;
		pHienTai = pTiepTheo;
	}

	this->_pDau = nullptr;
	this->_pCuoi = nullptr;
	this->_uiKichThuoc = 0;
}

/**********************************************************
* @Description Lay so phan tu hien co.
*
* @return So phan tu kieu std::size_t.
* @attention Dieu kien dau: Danh sach hop le.
* @attention Ket qua: Khong thay doi danh sach.
* @attention Su dung: _uiKichThuoc.
**********************************************************/
template <typename T>
std::size_t DanhSachLienKet<T>::layKichThuoc() const
{
	return this->_uiKichThuoc;
}

/**********************************************************
* @Description Kiem tra danh sach rong.
*
* @return true neu khong co phan tu; false neu co.
* @attention Dieu kien dau: Danh sach hop le.
* @attention Ket qua: Khong thay doi danh sach.
* @attention Su dung: lay kich thuoc noi bo.
**********************************************************/
template <typename T>
bool DanhSachLienKet<T>::laRong() const
{
	return this->_uiKichThuoc == 0;
}

/**********************************************************
* @Description Lay tham chieu hang tai vi tri bat dau tu 0.
*
* @return const T& tai vi tri yeu cau.
* @attention Dieu kien dau: uiViTri nho hon kich thuoc; neu khong thi nem std::out_of_range.
* @attention Ket qua: Khong thay doi danh sach.
* @attention Su dung: Duyet con tro TiepTheo.
**********************************************************/
template <typename T>
const T& DanhSachLienKet<T>::layTai(const std::size_t uiViTri) const
{
	if (uiViTri >= this->_uiKichThuoc)
	{
		throw std::out_of_range("DanhSachLienKet::layTai");
	}

	const NUT* pHienTai = this->_pDau;

	for (std::size_t uiChiSo = 0; uiChiSo < uiViTri; ++uiChiSo)
	{
		pHienTai = pHienTai->TiepTheo;
	}
	return pHienTai->DuLieu;
}

/**********************************************************
* @Description Tim phan tu dau tien thoa tieu chi, cho phep sua du lieu.
*
* @return T* den phan tu tim thay, hoac nullptr.
* @attention Dieu kien dau: tieuChi nhan T& va tra ve ket qua chuyen duoc sang bool.
* @attention Ket qua: Khong thay doi cau truc lien ket.
* @attention Su dung: Duyet node, goi tieuChi.
**********************************************************/
template <typename T>
template <typename TieuChi>
T* DanhSachLienKet<T>::timDauTien(TieuChi tieuChi)
{
	NUT* pHienTai = this->_pDau;

	while (pHienTai != nullptr)
	{
		if (tieuChi(pHienTai->DuLieu))
		{
			return &pHienTai->DuLieu;
		}

		pHienTai = pHienTai->TiepTheo;
	}

	return nullptr;
}

/**********************************************************
* @Description Tim phan tu dau tien thoa tieu chi tren danh sach const.
*
* @return const T* den phan tu tim thay, hoac nullptr.
* @attention Dieu kien dau: tieuChi nhan const T& va tra ve ket qua chuyen duoc sang bool.
* @attention Ket qua: Khong thay doi danh sach.
* @attention Su dung: Duyet node, goi tieuChi.
**********************************************************/
template <typename T>
template <typename TieuChi>
const T* DanhSachLienKet<T>::timDauTien(TieuChi tieuChi) const
{
	const NUT* pHienTai = this->_pDau;

	while (pHienTai != nullptr)
	{
		if (tieuChi(pHienTai->DuLieu))
		{
			return &pHienTai->DuLieu;
		}

		pHienTai = pHienTai->TiepTheo;
	}

	return nullptr;
}

/**********************************************************
* @Description Xoa node dau tien thoa tieu chi.
*
* @return true neu da xoa; false neu khong tim thay.
* @attention Dieu kien dau: tieuChi nhan T& va tra ve ket qua chuyen duoc sang bool.
* @attention Ket qua: Neu tim thay: xoa mot node va giam kich thuoc 1; neu khong: giu nguyen.
* @attention Su dung: Duyet node, noi lai con tro va delete.
**********************************************************/
template <typename T>
template <typename TieuChi>
bool DanhSachLienKet<T>::xoaDauTien(TieuChi tieuChi)
{
	NUT* pTruoc = nullptr;
	NUT* pHienTai = this->_pDau;

	while (pHienTai != nullptr)
	{
		if (tieuChi(pHienTai->DuLieu))
		{
			if (pTruoc == nullptr)
			{
				this->_pDau = pHienTai->TiepTheo;
			}
			else
			{
				pTruoc->TiepTheo = pHienTai->TiepTheo;
			}

			if (pHienTai == this->_pCuoi)
			{
				this->_pCuoi = pTruoc;
			}

			delete pHienTai;
			--this->_uiKichThuoc;
			return true;
		}

		pTruoc = pHienTai;
		pHienTai = pHienTai->TiepTheo;
	}

	return false;
}

/**********************************************************
* @Description Thuc hien hanh dong tren tung phan tu theo thu tu dau den cuoi.
*
* @return Khong co gia tri tra ve.
* @attention Dieu kien dau: hanhDong goi duoc voi const T&; khong lam mat hieu luc con tro lien ket.
* @attention Ket qua: Cau truc danh sach khong thay doi.
* @attention Su dung: Duyet NUT::TiepTheo va goi hanhDong.
**********************************************************/
template <typename T>
template <typename HanhDong>
void DanhSachLienKet<T>::duyet(HanhDong hanhDong) const
{
	const NUT* pHienTai = this->_pDau;

	while (pHienTai != nullptr)
	{
		hanhDong(pHienTai->DuLieu);
		pHienTai = pHienTai->TiepTheo;
	}
}

/**********************************************************
* @Description Sao chep tung phan tu cua danhSachNguon vao cuoi danh sach nay
*
* @return Khong co gia tri tra ve.
* @attention Ham noi bo, chi duoc goi tu copy constructor.
**********************************************************/
template <typename T>
void DanhSachLienKet<T>::saoChep(const DanhSachLienKet<T>& danhSachNguon)
{
	danhSachNguon.duyet([this](const T& duLieu)
	{
		this->themCuoi(duLieu);
	});
}

#endif
