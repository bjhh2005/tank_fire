// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
/*
*	生命组件类
*	类名：HealthComponent
*	继承自：UActorComponent
*	创建日期:2024年7月5日
*	简述：所有可伤害角色的血量组件用于管理敌方坦克的生命值，
*		  实现死亡事件，死亡延迟，死亡特效，死亡声音，死亡特效，死亡声音。
*		  实现生命恢复速度，调用造成伤害函数，获取生命值进度等等。
*/

/*
*	作者：张瑞欣
* 	日期：2024年7月5日
* 	版本：1.0
* 	更新功能：实现死亡事件，死亡延迟，死亡特效，死亡声音，死亡特效，死亡声音。
*			  实现生命恢复速度，调用造成伤害函数，获取生命值进度等等。
* 
 */

/*
*	作者：杨文韬
* 	日期：2024年7月6日
* 	版本：1.1
* 	更新功能：实现敌方坦克的生命值的实现，实现敌方坦克的对接。
*			  实现敌方坦克的死亡事件，死亡延迟，死亡特效，死亡声音，死亡特效，死亡声音。
*/

/*
* 	作者：张瑞欣
* 	日期：2024年7月10日
* 	版本：1.2
* 	更新功能：加入了生命值进度，便于实现坦克的进度条。
*/

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// 生命组件类

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANK_FIRE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	/*
	*	系统函数
	*/

	// Sets default values for this component's properties
	UHealthComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/*
	*	自定义函数
	*/
public:

	// 伤害函数
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Amount);

	// 获取生命值进度
	UFUNCTION(BlueprintCallable)
	float GetHealthProgress() { return health / MaxHealth; }

	// 恢复生命值
	void Recovery() { health = MaxHealth; }

	// 获取生命
	float GetHealth() { return health; }

	/*
	*   组件区域
	*/
protected:

	// 特效组件的引用
	UPROPERTY()
	UParticleSystemComponent* ActiveExplosionEffect;


public:	

	/*
	* 参数设置
	*/

	// 当前生命值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float health;

	// 最大生命值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100;

	// 用于判断是否进入恢复区域
	bool Isrecovery = false;
};
