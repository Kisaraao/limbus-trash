    $(function() {
        $('.slash').append(`
            <img src="./img/数值图标/斩击.webp" style="width:25px;">
        `);
        $('.stab').append(`
            <img src="./img/数值图标/突刺.webp" style="width:25px;">
        `);
        $('.strike').append(`
            <img src="./img/数值图标/打击.webp" style="width:25px;">
        `);

        $('.laziness').html(`
            <img src="./img/sin/怠惰.webp" class="sin_icon">
        `);
        $('.envy').html(`
            <img src="./img/sin/嫉妒.webp" class="sin_icon">
        `);
        $('.wrath').html(`
            <img src="./img/sin/暴怒.webp" class="sin_icon">
        `);
        $('.gluttony').html(`
            <img src="./img/sin/暴食.webp" class="sin_icon">
        `);
        $('.melancholy').html(`
            <img src="./img/sin/忧郁.webp" class="sin_icon">
        `);
        $('.pride').html(`
            <img src="./img/sin/傲慢.webp" class="sin_icon">
        `);
        $('.lust').html(`
            <img src="./img/sin/色欲.webp" class="sin_icon">
        `);

        $('.unbreakable_coin').html(`
            <img src="./img/coin/不可摧毁的硬币.webp" class="effect_icon">不可摧毁的硬币
            <x class="tip">
                <x>- 此类硬币不会因为拼点失败而被摧毁</x>
                <x>- 若攻击技能带有此类硬币，则受到攻击后以此类硬币进行攻击</x>
                <x>- 拼点失败时，使此类硬币的硬币威力固定为1</x>
            </x>
        `).css('color','darkred');
        $('.area_suppression_fire').html(`
            <img src="./img/effect/30px-广域乱射.webp" class="effect_icon">广域乱射
            <x class="tip">
                <x>- 本技能掷出硬币时，随机对其目标之一的1名单位进行攻击</x>
                <x>· 第一枚硬币必定命中主要目标</x>
                <x>· 每枚硬币的所有“命中时”效果与所有造成的伤害仅对以上效果中选择的单位生效</x>
            </x>
        `).css('color','#eed902');

        $('.protect').html(`
            <img src="./img/effect/15px-守护.webp" class="effect_icon">守护
            <x class="tip">- 本回合内受到的伤害-{0}0%（最多-100%）</x>
        `).css('color','#19b9c9');
        
        $('.strength').html(`
            <img src="./img/effect/15px-强壮.webp" class="effect_icon">强壮
            <x class="tip">- 本回合内攻击技能的最终威力+{0}</x>
        `).css('color','#c51b1b');
        
        $('.bind').html(`
            <img src="./img/effect/15px-束缚.webp" class="effect_icon">束缚
            <x class="tip">- 本回合内速度值-{0}。</x>
        `).css('color','#d57111');
        
        $('.defense_down').html(`
            <img src="./img/effect/15px-防御等级降低.webp" class="effect_icon">防御等级降低
            <x class="tip">- 本回合内防御等级-{0}。</x>
        `).css('color','#1f97d7');
        
        $('.attack_up').html(`
            <img src="./img/effect/15px-攻击等级提升.webp" class="effect_icon">攻击等级提升
            <x class="tip">- 本回合内攻击等级+{0}。</x>
        `).css('color','darkred');
        
        $('.chip_up').html(`
            <img src="./img/effect/15px-拼点威力提升.webp" class="effect_icon">拼点威力提升
            <x class="tip">- 进行拼点时，拼点威力增加等同于本效果层数的数值。</x>
        `).css('color','#daa520');
        
        $('.rupture').html(`
            <img src="./img/effect/15px-破裂.webp" class="effect_icon">破裂
            <x class="tip">- 下{1}次被攻击时，额外受到{0}点固定伤害。</x>
        `).css('color','#20dfb5');
        
        $('.sink').html(`
            <img src="./img/effect/15px-沉沦.webp" class="effect_icon">沉沦
            <x class="tip">- 下{1}次被攻击时，额外受到{0}点固定理智伤害。(没有理智值的目标则受到忧郁属性伤害)</x>
        `).css('color','#1475e3');
        
        $('.sink_overflow').html(`
            <img src="./img/effect/15px-沉沦泛滥.webp" class="effect_icon">沉沦泛滥
            <x class="tip">- 造成（沉沦层数×沉沦强度）理智伤害，随后移除沉沦若目标的理智值降至-45，则溢出的理智伤害转化为等量的忧郁伤害。（对于没有理智值的目标，造成的理智伤害全部转化为等量的忧郁伤害）</x>
        `).css('color','#1475e3');
        
        $('.burn').html(`
            <img src="./img/effect/15px-烧伤.webp" class="effect_icon">烧伤
            <x class="tip">- 回合结束时：受到{0}点固定伤害。持续{1}回合。</x>
        `).css('color','#dd2543');
        
        $('.bleed').html(`
            <img src="./img/effect/15px-流血.webp" class="effect_icon">流血
            <x class="tip">- 下{1}次掷出硬币时受到{0}点固定伤害。</x>
        `).css('color','#bd1d1f');
        
        $('.tremor').html(`
            <img src="./img/effect/15px-震颤.webp" class="effect_icon">震颤
            <x class="tip">- 在{1}回合内，受到造成震颤引爆的攻击时，混乱阈值前移{0}。</x>
        `).css('color','#eac379');
        
        $('.tremor_boom').html(`
            <img src="./img/effect/15px-震颤引爆.webp" class="effect_icon">震颤引爆
            <x class="tip">- 使目标的混乱阈值前移与震颤强度相同的数值。</x>
        `).css('color','#eac379');
        
        $('.charge').html(`
            <img src="./img/effect/15px-充能.webp" class="effect_icon">充能
            <x class="tip">- 特定技能发动附加效果所需的资源。最大20层。回合结束时本效果的层数降低1层。累计消耗层数：{2}</x>
        `).css('color','#14cecc');
        
        $('.breath').html(`
            <img src="./img/effect/15px-呼吸法.webp" class="effect_icon">呼吸法
            <x class="tip">- 下{1}次攻击命中时有{0}x5%的概率产生暴击。</x>
        `).css('color','#bfc5c5');

        $('.vulnerable').html(`
            <img src="./img/effect/15px-易损.webp" class="effect_icon">易损
            <x class="tip">- 本回合内受到的伤害+{0}0%（最多+100%）</x>
        `).css('color','#a215ba');

        $('.damage_up').html(`
            <img src="./img/effect/15px-伤害强化.webp" class="effect_icon">伤害强化
            <x class="tip">- 本回合内造成的伤害+{0}0%（最多+100%）</x>
        `).css('color','#bf2521');
    });